#ifndef _PluginSDK_PluginSDK_h_
#define _PluginSDK_PluginSDK_h_

#include "PluginTypes.h"

#ifdef GUI
#include <CtrlLib/CtrlLib.h>
#endif

namespace PluginSDK {

class PluginProcessor {
public:
	virtual ~PluginProcessor() {}

	virtual void Prepare(const AudioConfig& config);
	virtual void Reset();
	virtual void Process(ProcessContext& ctx) = 0;

	virtual void SetParameter(const Upp::String& id, double value);
	virtual double GetParameter(const Upp::String& id) const;
	
	virtual Upp::String GetURI() const { return ""; }
	virtual Upp::String GetName() const { return "Plugin"; }

	ParameterSet& Parameters();
	const ParameterSet& Parameters() const;
	GraphVisualization& Graph();
	const GraphVisualization& Graph() const;

protected:
	ParameterSet parameter_set;
	AudioConfig current_config;
	GraphVisualization graph; // Add GraphVisualization member
};

#ifdef GUI

class PluginEditor : public Upp::Ctrl {
public:
	typedef PluginEditor CLASSNAME;
	PluginEditor() {}
	virtual ~PluginEditor() {}

	virtual void SetProcessor(PluginProcessor* p) { processor = p; }
	virtual void SyncToProcessor() {}
	virtual void SyncFromProcessor() {}

protected:
	PluginProcessor* processor = nullptr;
};

class PluginWindow : public Upp::TopWindow {
public:
	typedef PluginWindow CLASSNAME;
	PluginWindow() {
		Sizeable().Zoomable();
		SetRect(0, 0, 800, 600);
		AddFrame(menuBar);
		
		// Add simple transport bar at top
		Add(transportBar.TopPos(0, 30).HSizePos());
		transportBar.Add(playBtn.LeftPos(5, 60).VSizePos(5, 5));
		transportBar.Add(stopBtn.LeftPos(70, 60).VSizePos(5, 5));
		transportBar.Add(timeDisplay.LeftPos(140, 100).VSizePos(5, 5));
		
		playBtn.SetLabel("Play");
		stopBtn.SetLabel("Stop");
		timeDisplay.SetAlign(Upp::ALIGN_CENTER);
		timeDisplay.SetFont(Upp::Arial(12).Bold());
		
		playBtn << [=] { WhenPlay(); };
		stopBtn << [=] { WhenStop(); };
	}

	void SetEditor(PluginEditor& e) {
		if(editor) editor->Remove();
		editor = &e;
		Add(e.VSizePos(30, 0).HSizePos());
	}
	
	void SetMenuBar(void (*menu)(Upp::Bar&)) {
		menuBar.Set(menu);
	}
	
	void SetTime(const Upp::String& t) { timeDisplay.SetLabel(t); }
	void SetPlaying(bool b) { playBtn.SetLabel(b ? "Pause" : "Play"); }

	Upp::Event<> WhenPlay;
	Upp::Event<> WhenStop;

private:
	PluginEditor* editor = nullptr;
	Upp::MenuBar menuBar;
	Upp::StaticRect transportBar;
	Upp::Button playBtn;
	Upp::Button stopBtn;
	Upp::Label timeDisplay;
};

#endif // GUI

} // namespace PluginSDK

#endif
