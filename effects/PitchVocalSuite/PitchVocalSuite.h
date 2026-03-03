#ifndef _PitchVocalSuite_PitchVocalSuite_h_
#define _PitchVocalSuite_PitchVocalSuite_h_

#include <CtrlLib/CtrlLib.h>
#include <AudioUI/AudioUI.h>
#include <PluginSDK/PluginSDK.h>

using namespace Upp;
using namespace PluginSDK;

// DSP Processor for PitchVocalSuite
class PitchVocalProcessor : public PluginProcessor {
public:
	PitchVocalProcessor();
	virtual void Process(ProcessContext& ctx) override;
};

// Custom control for pitch graph editing
class PitchGraphEditor : public Ctrl {
public:
	typedef PitchGraphEditor CLASSNAME;
	PitchGraphEditor();

	virtual void Paint(Draw& w) override;
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
};

// Main editor container
class PitchVocalEditor : public PluginEditor {
public:
	typedef PitchVocalEditor CLASSNAME;
	PitchVocalEditor();

private:
	PitchVocalTopBar topBar;
	PitchGraphEditor graphEditor;
	WaveformStrip waveformStrip;
};

#endif
