#ifndef _ProjectWindow_ProjectWindow_h_
#define _ProjectWindow_ProjectWindow_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

class ProjectToolbarPane : public ToolBar {
public:
	typedef ProjectToolbarPane CLASSNAME;
	ProjectToolbarPane();

	void SetTransportEnabled(bool enabled);
	void SetSnapEnabled(bool enabled);
	void SetProjectTitle(const Upp::String& title);

private:
	void BuildToolbar();
	void AddToolButton(const Upp::String& label, Button& button);
	void AddToolButton(const Upp::String& label, Button& button, int width);
	void DummyAction();

	Option activateProject;
	Option constrainDelayComp;
	Option toggleInspector;
	Option toggleInfoLine;
	Option toggleOverview;
	Option togglePool;
	Option toggleMixer;
	Button automationPanel;
	DropList automationMode;
	Button prevMarker;
	Button nextMarker;
	Button loopToggle;
	Button stopTransport;
	Button playTransport;
	Button recordTransport;
	Array<Button> editingToolButtons;
	DropList pitchSelector;
	Option autoScroll;
	Option autoScrollSuspend;
	Option snapToggle;
	DropList snapType;
	DropList quantizeBase;
	DropList quantizeValue;
	Option snapZeroCrossing;
	Button colorPicker;
	Label projectName;
};

class ProjectInfoLinePane : public ParentCtrl {
public:
	typedef ProjectInfoLinePane CLASSNAME;
	static constexpr int INFO_HEIGHT = 28;

	ProjectInfoLinePane();

	void ShowMidiColumns();
	void ShowAudioColumns();

private:
	void BuildMidiColumns();
	void BuildAudioColumns();

	TabCtrl infoTabs;
	ArrayCtrl midiInfo;
	ArrayCtrl audioInfo;
};

class InspectorPane : public ParentCtrl {
public:
	typedef InspectorPane CLASSNAME;
	InspectorPane();

	void SetTrackType(const Upp::String& type);
	void RefreshPanels();
	void SetPanels(const Upp::Vector<ValueMap>& panels);

private:
	ArrayCtrl panelList;
	Label trackLabel;
	Upp::Vector<ValueMap> panelState;
};

class TrackListPane : public ParentCtrl {
public:
	typedef TrackListPane CLASSNAME;
	TrackListPane();

	void SetTracks(const Upp::Vector<Upp::String>& tracks);
	void SetToolbarEnabled(bool enabled);
	void Clear();
	void AppendTrack(const Upp::String& name, const Upp::String& controls, const Upp::String& detail);

private:
	ToolBar trackToolbar;
	ArrayCtrl trackTable;
	void BuildToolbar();
	void PopulateDemoRows();
};

class ProjectAreaPane : public ParentCtrl {
public:
	typedef ProjectAreaPane CLASSNAME;
	ProjectAreaPane();

	void SetRulerFormat(const Upp::String& format);
	void SetZoomState(int horizontal, int vertical);
	void RefreshClips();

private:
	Label ruler;
	Label formatLabel;
	SliderCtrl horizontalZoom;
	SliderCtrl verticalZoom;
	StaticRect clipCanvas;
};

class ProjectWindowCtrl : public ParentCtrl {
public:
	typedef ProjectWindowCtrl CLASSNAME;
	static constexpr int TOOLBAR_HEIGHT = 64;
	static constexpr int HEADER_HEIGHT = TOOLBAR_HEIGHT + ProjectInfoLinePane::INFO_HEIGHT;

	ProjectWindowCtrl();

	void InitDefaultLayout();
	void SetProjectTitle(const Upp::String& title);
	void BindTimelineModel(Callback whenTimelineChanged);
	void BindTrackModel(Callback whenTrackModelChanged);
	void BindInspectorSource(Callback whenInspectorChanged);
	void SetProjectZoomState(int horizontal, int vertical);
	void UpdateTrackList(const Upp::Vector<ValueMap>& entries);
	void UpdateInspectorPanels(const Upp::Vector<ValueMap>& panels, const Upp::String& caption);
	void UpdateWorkAreaState(const ValueMap& state);

private:
	void ConfigureSplitters();
	void InitDemoData();

	ProjectToolbarPane toolbar;
	ProjectInfoLinePane infoLine;
	Splitter horizontalSplit;
	Splitter middleSplit;
	InspectorPane inspector;
	TrackListPane trackList;
	ProjectAreaPane projectArea;
	Callback onTimelineChanged;
	Callback onTrackModelChanged;
	Callback onInspectorChanged;
	Upp::Vector<ValueMap> cachedTrackEntries;
	Upp::Vector<ValueMap> cachedInspectorPanels;
	ValueMap cachedWorkArea;
};

class ProjectWindowHost : public TopWindow {
public:
	typedef ProjectWindowHost CLASSNAME;
	ProjectWindowHost();

	ProjectWindowCtrl& GetView();
	void OpenProjectWindow();
	void CloseProjectWindow();
	void SetProjectTitle(const Upp::String& title);

private:
	ProjectWindowCtrl view;
};

}

#endif
