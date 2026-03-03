#ifndef _PitchVocalSuite_PitchVocalSuite_h_
#define _PitchVocalSuite_PitchVocalSuite_h_

#include <CtrlLib/CtrlLib.h>
#include <AudioUI/AudioUI.h>
#include <AudioAnalysis/AudioAnalysis.h>
#include <PluginSDK/PluginSDK.h>

using namespace Upp;
using namespace PluginSDK;

struct PitchVocalViewport {
	double zoomX = 100.0; // pixels per second/beat
	double scrollX = 0.0; // scroll offset in seconds/beats
	double zoomY = 20.0;  // pixels per semitone
	double scrollY = 60.0; // center MIDI note
};

// DSP Processor for PitchVocalSuite
class PitchVocalProcessor : public PluginProcessor {
public:
	PitchVocalProcessor();
	virtual void Process(ProcessContext& ctx) override;

	virtual Upp::String GetURI() const override;
	virtual Upp::String GetName() const override;

	const Vector<am::PitchPoint>& GetPitchPoints() const { return pitchPoints; }
	const Vector<float>& GetWaveformBuffer() const { return waveformBuffer; }

private:
	am::PitchAnalysisEngine pitchEngine;
	Vector<am::PitchPoint> pitchPoints;
	Vector<float> waveformBuffer;
	int waveformBufferSize = 2048;
};

// Custom control for pitch graph editing
class PitchGraphEditor : public Ctrl {
public:
	typedef PitchGraphEditor CLASSNAME;
	PitchGraphEditor();

	void SetProcessor(PitchVocalProcessor* p) { processor = p; }
	void SetViewport(PitchVocalViewport* v) { viewport = v; }
	virtual void Paint(Draw& w) override;
	virtual void MouseWheel(Point p, int zdelta, dword keyflags) override;
	virtual void MiddleDown(Point p, dword keyflags) override;
	virtual void MouseMove(Point p, dword keyflags) override;

private:
	PitchVocalProcessor* processor = nullptr;
	PitchVocalViewport* viewport = nullptr;
	Point lastMousePos;
};

// Custom control for waveform visualization
class WaveformStrip : public Ctrl {
public:
	typedef WaveformStrip CLASSNAME;
	WaveformStrip();

	void SetProcessor(PitchVocalProcessor* p) { processor = p; }
	void SetViewport(PitchVocalViewport* v) { viewport = v; }
	virtual void Paint(Draw& w) override;

private:
	PitchVocalProcessor* processor = nullptr;
	PitchVocalViewport* viewport = nullptr;
};

// Top bar for global controls
class PitchVocalTopBar : public ParentCtrl {
public:
	typedef PitchVocalTopBar CLASSNAME;
	PitchVocalTopBar();

	virtual void Paint(Draw& w) override;

	Event<> WhenAction;

	int GetAlgorithm() const { return algorithm.GetIndex(); }
	void SetAlgorithm(int i) { algorithm.SetIndex(i); }

	double GetSpeed() const { return correctionSpeed.GetData(); }
	void SetSpeed(double v) { correctionSpeed.SetData(v); }

	double GetVibrato() const { return vibratoAmount.GetData(); }
	void SetVibrato(double v) { vibratoAmount.SetData(v); }

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
	virtual void SyncToProcessor() override;
	virtual void SyncFromProcessor() override;

private:
	void OnTopBarAction();

	PitchVocalTopBar topBar;
	PitchGraphEditor graphEditor;
	WaveformStrip waveformStrip;
	PitchVocalViewport viewport;
};

#endif
