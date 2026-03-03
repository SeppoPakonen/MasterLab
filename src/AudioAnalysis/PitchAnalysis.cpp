#include "PitchAnalysis.h"
#include <Math/FFT.h>
#include <cmath>

namespace am {

PitchAnalysisEngine::PitchAnalysisEngine()
{
}

void PitchAnalysisEngine::Analyze(const float* samples, int count, double startTime, Vector<PitchPoint>& points)
{
	if(count < windowSize) return;

	// windowSize is power of 2 for FFT efficiency
	// We zero-pad to double the size to avoid cyclic autocorrelation artifacts
	int fftSize = windowSize * 2;
	
	for(int i = 0; i <= count - windowSize; i += hopSize) {
		Vector<double> buffer;
		buffer.SetCount(fftSize, 0.0);
		
		double energy = 0;
		for(int j = 0; j < windowSize; j++) {
			double s = samples[i + j];
			// Apply Hann window
			double w = 0.5 * (1.0 - cos(2.0 * M_PI * j / (windowSize - 1)));
			buffer[j] = s * w;
			energy += (s * w) * (s * w);
		}
		
		energy = sqrt(energy / windowSize);
		
		if(energy > 0.005) { // Lower threshold for autocorrelation
			// 1. Forward FFT
			Vector<Complex> spec = RealFFT(buffer);
			
			// 2. Power Spectrum
			for(int j = 0; j < spec.GetCount(); j++) {
				double mag = spec[j].real() * spec[j].real() + spec[j].imag() * spec[j].imag();
				spec[j] = Complex(mag, 0);
			}
			
			// 3. Inverse FFT to get Autocorrelation
			Vector<double> acf = InverseRealFFT(spec);
			
			// 4. Peak Detection in ACF
			// Human pitch range: 50Hz to 1500Hz
			int minPeriod = (int)(sampleRate / 1500.0);
			int maxPeriod = (int)(sampleRate / 50.0);
			if(maxPeriod >= windowSize) maxPeriod = windowSize - 1;
			
			int bestLag = -1;
			double maxVal = -1e10;
			
			for(int lag = minPeriod; lag <= maxPeriod; lag++) {
				if(acf[lag] > maxVal) {
					maxVal = acf[lag];
					bestLag = lag;
				}
			}
			
			if(bestLag > 0 && acf[bestLag] > 0.3 * acf[0]) { // 0.3 is a basic confidence threshold
				// Parabolic interpolation for sub-bin accuracy
				double alpha = acf[bestLag - 1];
				double beta = acf[bestLag];
				double gamma = acf[bestLag + 1];
				double p = 0.5 * (alpha - gamma) / (alpha - 2.0 * beta + gamma);
				
				double preciseLag = bestLag + p;
				double freq = sampleRate / preciseLag;
				double confidence = acf[bestLag] / acf[0];
				
				double time = startTime + (double)i / sampleRate;
				points.Add(PitchPoint(time, freq, confidence));
			}
		}
	}
}

double PitchAnalysisEngine::FrequencyToMidi(double freq)
{
	if(freq <= 0) return 0;
	return 69.0 + 12.0 * log2(freq / 440.0);
}

double PitchAnalysisEngine::MidiToFrequency(double midi)
{
	return 440.0 * pow(2.0, (midi - 69.0) / 12.0);
}

} // namespace am
