#ifndef _PitchVocalSuiteCore_PitchVocalSuiteCore_h_
#define _PitchVocalSuiteCore_PitchVocalSuiteCore_h_

#include <PluginSDK/PluginSDK.h>
#include <AudioAnalysis/AudioAnalysis.h>
#include <DSP/PhaseVocoder.h>

using namespace Upp;

// Forward declare for editor to use
struct PitchNote : Moveable<PitchNote> {
	double startTime = 0, duration = 0;
	int midiNote = 60;
	bool selected = false;
	
	void Jsonize(JsonIO& jio) {
		jio("start", startTime)("duration", duration)("midi", midiNote);
	}
};

class PitchVocalProcessor : public PluginSDK::PluginProcessor {
public:
	PitchVocalProcessor();
	
	virtual void Process(PluginSDK::ProcessContext& ctx) override;
	
	virtual String GetURI() const override { return "https://masterlab.com/plugins/pitch-vocal-suite"; }
	virtual String GetName() const override { return "Pitch Vocal Suite"; }
	
	void LoadFullAudio(const am::AudioBuffer& buffer, const String& path);
	
	Vector<PitchNote>& GetNotes() { return notes; }
	const Vector<am::PitchPoint>& GetPitchPoints() const { return pitchPoints; }
	const Vector<float>& GetFullWaveform() const { return fullWaveform; }
	
	Event<String> WhenLog;

private:
	String GetCachePath(const String& path);
	
	double pitch_shift_semitones = 0.0;
	DSP::PhaseVocoder phaseVocoder;
	am::AudioBuffer fullAudioBuffer;
	am::PitchAnalysisEngine pitchEngine;
	Vector<am::PitchPoint> pitchPoints;
	Vector<float> fullWaveform;
	Vector<PitchNote> notes;
	
	void Log(String s) { if(WhenLog) WhenLog(s); }
};

#endif
