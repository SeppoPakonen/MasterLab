#include "PhaseVocoder.h"

namespace DSP {

PhaseVocoder::PhaseVocoder()
{
	// Hann window
	for(int i = 0; i < windowSize; i++) {
		window.Add(0.5 * (1 - cos(2 * M_PI * i / (windowSize - 1))));
	}
}

void PhaseVocoder::Process(AudioBuffer& buffer, double pitchShiftRatio)
{
	if (buffer.GetChannels() == 0) return;
	
	Vector<Vector<Complex>> frames;
	STFT(buffer.data[0], frames);
	
	int nFrames = frames.GetCount();
	int nBins = frames[0].GetCount();
	
	Vector<double> lastPhase(nBins, 0.0);
	Vector<double> phaseAccum(nBins, 0.0);
	
	for (int i = 0; i < nFrames; i++) {
		for (int j = 0; j < nBins; j++) {
			double mag = abs(frames[i][j]);
			double phase = arg(frames[i][j]);
			
			double phaseDev = phase - lastPhase[j];
			lastPhase[j] = phase;
			
			double freq = phaseDev / (2.0 * M_PI * hopSize / buffer.rate);
			double newFreq = freq * pitchShiftRatio;
			
			phaseAccum[j] += 2.0 * M_PI * newFreq * hopSize / buffer.rate;
			
			frames[i][j] = std::polar(mag, phaseAccum[j]);
		}
	}
	
	ISTFT(frames, buffer.data[0]);
}

void PhaseVocoder::STFT(const Vector<float>& input, Vector<Vector<Complex>>& frames)
{
	int nFrames = (input.GetCount() - windowSize) / hopSize + 1;
	frames.SetCount(nFrames);

	for (int i = 0; i < nFrames; i++) {
		Vector<double> frame;
		frame.SetCount(windowSize);
		for (int j = 0; j < windowSize; j++) {
			frame[j] = input[i * hopSize + j] * window[j];
		}
		
		frames[i] = RealFFT(frame);
	}
}

void PhaseVocoder::ISTFT(const Vector<Vector<Complex>>& frames, Vector<float>& output)
{
	int nFrames = frames.GetCount();
	int outSize = (nFrames - 1) * hopSize + windowSize;
	output.SetCount(outSize, 0.0f);
	
	for (int i = 0; i < nFrames; i++) {
		Vector<double> frame = InverseRealFFT(frames[i]);
		
		for(int j = 0; j < windowSize; j++) {
			output[i * hopSize + j] += frame[j] * window[j];
		}
	}
}

}
