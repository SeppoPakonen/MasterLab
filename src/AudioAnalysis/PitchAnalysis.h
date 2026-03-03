#ifndef _AudioAnalysis_PitchAnalysis_h_
#define _AudioAnalysis_PitchAnalysis_h_

#include <Core/Core.h>
#include <AudioCore/AudioCore.h>

namespace am {

using namespace Upp;

struct PitchPoint : public Moveable<PitchPoint> {
	double time;
	double frequency;
	double confidence;
	
	PitchPoint() : time(0), frequency(0), confidence(0) {}
	PitchPoint(double t, double f, double c) : time(t), frequency(f), confidence(c) {}
};

class PitchAnalysisEngine {
public:
	PitchAnalysisEngine();
	virtual ~PitchAnalysisEngine() {}

	void SetSampleRate(double rate) { sampleRate = rate; }
	
	// Analyze a buffer and append points to the provided vector
	virtual void Analyze(const float* samples, int count, double startTime, Vector<PitchPoint>& points);

	// Static utility for frequency to MIDI note conversion
	static double FrequencyToMidi(double freq);
	static double MidiToFrequency(double midi);

protected:
	double sampleRate = 44100.0;
	int windowSize = 2048;
	int hopSize = 512;
};

} // namespace am

#endif
