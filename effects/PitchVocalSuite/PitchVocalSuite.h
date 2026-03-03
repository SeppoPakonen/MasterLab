#ifndef _PitchVocalSuite_PitchVocalSuite_h_
#define _PitchVocalSuite_PitchVocalSuite_h_

#include <CtrlLib/CtrlLib.h>
#include <AudioUI/AudioUI.h>
#include <AudioAnalysis/AudioAnalysis.h>
#include <PluginSDK/PluginSDK.h>

using namespace Upp;
using namespace PluginSDK;

// DSP Processor for PitchVocalSuite
class PitchVocalProcessor : public PluginProcessor {
public:
	PitchVocalProcessor();
	virtual void Process(ProcessContext& ctx) override;

	virtual Upp::String GetURI() const override;
	virtual Upp::String GetName() const override;

	const Vector<am::PitchPoint>& GetPitchPoints() const { return pitchPoints; }

private:
	am::PitchAnalysisEngine pitchEngine;
	Vector<am::PitchPoint> pitchPoints;
};

// Custom control for pitch graph editing
class PitchGraphEditor : public Ctrl {
public:
	typedef PitchGraphEditor CLASSNAME;
	PitchGraphEditor();

	void SetProcessor(PitchVocalProcessor* p) { processor = p; }
	virtual void Paint(Draw& w) override;

private:
	PitchVocalProcessor* processor = nullptr;
};

// Custom control for waveform visualization
class WaveformStrip : public Ctrl {
public:
	typedef WaveformStrip CLASSNAME;
	WaveformStrip();

	virtual void Paint(Draw& w) override;
};

// Top bar for global controls
class PitchVocalTopBar : public ParentCtrl {
public:
	typedef PitchVocalTopBar CLASSNAME;
	PitchVocalTopBar();

	virtual void Paint(Draw& w) override;

private:
	DropList algorithm;
	SliderCtrl correctionSpeed;
	SliderCtrl vibratoAmount;
	
	Label lblAlgorithm;
	Label lblSpeed;
	Label lblVibrato;
};

// Main editor container
class PitchVocalEditor : public PluginEditor {
public:
	typedef PitchVocalEditor CLASSNAME;
	PitchVocalEditor();

	virtual void SetProcessor(PluginProcessor* p) override;

private:
	PitchVocalTopBar topBar;
	PitchGraphEditor graphEditor;
	WaveformStrip waveformStrip;
};

#endif
