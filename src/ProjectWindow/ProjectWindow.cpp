#include "ProjectWindow.h"

namespace am {

ProjectToolbarPane::ProjectToolbarPane() {
	SetFrame(ThinInsetFrame());
	BuildToolbar();
}

void ProjectToolbarPane::BuildToolbar() {
	Clear();
	activateProject.SetLabel("Activate Project");
	activateProject = true;
	activateProject.WhenAction = THISBACK(DummyAction);
	Add(activateProject, 130);

	constrainDelayComp.SetLabel("Constrain Delay Comp");
	constrainDelayComp.WhenAction = THISBACK(DummyAction);
	Add(constrainDelayComp, 150);

	Separator();
	toggleInspector.SetLabel("Inspector");
	toggleInspector = true;
	toggleInspector.WhenAction = THISBACK(DummyAction);
	Add(toggleInspector, 90);

	toggleInfoLine.SetLabel("Info Line");
	toggleInfoLine = true;
	toggleInfoLine.WhenAction = THISBACK(DummyAction);
	Add(toggleInfoLine, 90);

	toggleOverview.SetLabel("Overview");
	toggleOverview.WhenAction = THISBACK(DummyAction);
	Add(toggleOverview, 90);

	togglePool.SetLabel("Pool");
	togglePool.WhenAction = THISBACK(DummyAction);
	Add(togglePool, 80);

	toggleMixer.SetLabel("Mixer");
	toggleMixer.WhenAction = THISBACK(DummyAction);
	Add(toggleMixer, 80);

	Separator();
	automationPanel.SetLabel("Automation Panel");
	automationPanel.WhenAction = THISBACK(DummyAction);
	Add(automationPanel, 150);

	automationMode.Add("Touch");
	automationMode.Add("Auto-Latch");
	automationMode.Add("Crossover");
	automationMode.SetIndex(0);
	Add(automationMode, 130);

	Separator();
	AddToolButton("Prev", prevMarker, 70);
	AddToolButton("Next", nextMarker, 70);
	AddToolButton("Loop", loopToggle, 70);
	AddToolButton("Stop", stopTransport, 70);
	AddToolButton("Play", playTransport, 70);
	AddToolButton("Record", recordTransport, 80);

	Separator();
	static const char* toolNames[] = {
		"Select", "Range", "Split", "Glue", "Erase", "Zoom",
		"Mute", "Time Warp", "Draw", "Line", "Play Tool", "Colorize"
	};
	for(const char* name : toolNames) {
		Button& btn = editingToolButtons.Create<Button>();
		AddToolButton(name, btn);
	}

	pitchSelector.Add("-");
	static const char* notes[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
	for(const char* note : notes)
		pitchSelector.Add(note);
	pitchSelector.SetIndex(0);
	Add(pitchSelector, 90);

	Separator();
	autoScroll.SetLabel("Auto-Scroll");
	autoScroll.WhenAction = THISBACK(DummyAction);
	Add(autoScroll, 110);

	autoScrollSuspend.SetLabel("Suspend Edit");
	autoScrollSuspend.WhenAction = THISBACK(DummyAction);
	Add(autoScrollSuspend, 120);

	snapToggle.SetLabel("Snap");
	snapToggle = true;
	snapToggle.WhenAction = THISBACK(DummyAction);
	Add(snapToggle, 70);

	snapType.Add("Grid");
	snapType.Add("Relative Grid");
	snapType.Add("Events");
	snapType.Add("Shuffle");
	snapType.Add("Cursor");
	snapType.Add("Grid & Cursor");
	snapType.Add("Events & Cursor");
	snapType.Add("Events, Grid & Cursor");
	snapType.SetIndex(0);
	Add(snapType, 150);

	Separator();
	quantizeBase.Add("Bar");
	quantizeBase.Add("Beat");
	quantizeBase.Add("Use Quantize");
	quantizeBase.SetIndex(0);
	Add(quantizeBase, 120);

	quantizeValue.Add("1/1");
	quantizeValue.Add("1/2");
	quantizeValue.Add("1/4");
	quantizeValue.Add("1/8");
	quantizeValue.Add("1/16");
	quantizeValue.Add("1/4T");
	quantizeValue.Add("1/8T");
	quantizeValue.Add("1/16T");
	quantizeValue.Add("Setup...");
	quantizeValue.SetIndex(2);
	Add(quantizeValue, 120);

	Separator();
	snapZeroCrossing.SetLabel("Snap Zero");
	snapZeroCrossing.WhenAction = THISBACK(DummyAction);
	Add(snapZeroCrossing, 110);

	colorPicker.SetLabel("Color Picker");
	colorPicker.WhenAction = THISBACK(DummyAction);
	Add(colorPicker, 130);

	Separator();
	projectName.SetLabel("Untitled Project");
	projectName.SetFrame(NullFrame());
	Add(projectName, 200);
}

void ProjectToolbarPane::AddToolButton(const String& label, Button& button) {
	AddToolButton(label, button, 90);
}

void ProjectToolbarPane::AddToolButton(const String& label, Button& button, int width) {
	button.SetLabel(label);
	button.WhenAction = THISBACK(DummyAction);
	Add(button, width);
}

void ProjectToolbarPane::DummyAction() {
	// Placeholder for command wiring
}

void ProjectToolbarPane::SetTransportEnabled(bool enabled) {
	prevMarker.Enable(enabled);
	nextMarker.Enable(enabled);
	loopToggle.Enable(enabled);
	stopTransport.Enable(enabled);
	playTransport.Enable(enabled);
	recordTransport.Enable(enabled);
}

void ProjectToolbarPane::SetSnapEnabled(bool enabled) {
	snapToggle.Enable(enabled);
	snapType.Enable(enabled);
	quantizeBase.Enable(enabled);
	quantizeValue.Enable(enabled);
	snapZeroCrossing.Enable(enabled);
}

void ProjectToolbarPane::SetProjectTitle(const String& title) {
	projectName.SetLabel(title);
}

ProjectInfoLinePane::ProjectInfoLinePane() {
	SetFrame(ThinInsetFrame());
	Add(infoTabs.SizePos());

	BuildMidiColumns();
	BuildAudioColumns();

	infoTabs.Add(midiInfo, "MIDI");
	infoTabs.Add(audioInfo, "Audio");
	infoTabs.Set(0);
}

void ProjectInfoLinePane::BuildMidiColumns() {
	midiInfo.Reset();
	midiInfo.Enable(false);
	midiInfo.AddColumn("Name");
	midiInfo.AddColumn("Start");
	midiInfo.AddColumn("End");
	midiInfo.AddColumn("Length");
	midiInfo.AddColumn("Offset");
	midiInfo.AddColumn("Mute");
	midiInfo.AddColumn("Lock");
	midiInfo.AddColumn("Transpose");
	midiInfo.AddColumn("Global Transpose");
	midiInfo.AddColumn("Velocity");
	midiInfo.AddColumn("Key");
	midiInfo.Add("MIDI Part", "1.01.00.000", "2.01.00.000", "1.00.00.000", "0.00.00.000", "Off", "Position", "0", "Follow", "100%", "C");
}

void ProjectInfoLinePane::BuildAudioColumns() {
	audioInfo.Reset();
	audioInfo.Enable(false);
	audioInfo.AddColumn("File");
	audioInfo.AddColumn("Description");
	audioInfo.AddColumn("Start");
	audioInfo.AddColumn("End");
	audioInfo.AddColumn("Length");
	audioInfo.AddColumn("Offset");
	audioInfo.AddColumn("Snap");
	audioInfo.AddColumn("Fade In");
	audioInfo.AddColumn("Fade Out");
	audioInfo.AddColumn("Volume");
	audioInfo.AddColumn("Lock");
	audioInfo.AddColumn("Transpose");
	audioInfo.AddColumn("Fine Tune");
	audioInfo.AddColumn("Global Transpose");
	audioInfo.AddColumn("Key");
	audioInfo.AddColumn("Mute");
	audioInfo.Add("Audio Clip", "Vocal take", "1.01.00.000", "1.03.00.000", "0.02.00.000", "0.00.00.000", "Grid", "Linear", "Linear", "0.0 dB", "Unlocked", "0", "0", "Follow", "C", "Off");
}

void ProjectInfoLinePane::ShowMidiColumns() {
	infoTabs.Set(0);
}

void ProjectInfoLinePane::ShowAudioColumns() {
	infoTabs.Set(1);
}

InspectorPane::InspectorPane() {
	SetFrame(ThinInsetFrame());
	Add(trackLabel.TopPos(4, 20).HSizePos(4, 4));
	trackLabel.SetText("Instrument Track Inspector");

	panelList.AddColumn("Panel").HeaderTab().AlignLeft();
	panelList.NoHeader();
	panelList.Enable(false);
	panelList.SetFrame(InsetFrame());
	Add(panelList.VSizePos(28, 4).HSizePos(4, 4));
	RefreshPanels();
}

void InspectorPane::SetTrackType(const String& type) {
	trackLabel.SetText(type + " Inspector");
}

void InspectorPane::RefreshPanels() {
	panelList.Clear();
	if(panelState.IsEmpty()) {
		panelList.Add("Track Controls");
		panelList.Add("VST Expression");
		panelList.Add("MIDI Inserts");
		panelList.Add("Equalizer");
		panelList.Add("Sends");
		panelList.Add("Channel Settings");
		panelList.Add("Notepad");
		panelList.Add("Quick Controls");
	}
	else {
		for(const ValueMap& panel : panelState) {
			String name = const_cast<ValueMap&>(panel).Get("title", "Panel");
			panelList.Add(name);
		}
	}
	panelList.Refresh();
}

void InspectorPane::SetPanels(const Vector<ValueMap>& panels) {
	panelState <<= panels;
}

TrackListPane::TrackListPane() {
	SetFrame(ThinInsetFrame());
	Add(trackToolbar.TopPos(0, 24).HSizePos());
	trackToolbar.SetFrame(NullFrame());
	BuildToolbar();

	trackTable.AddColumn("Track");
	trackTable.AddColumn("Controls");
	trackTable.AddColumn("Details");
	trackTable.ColumnWidths("140 220 160");
	trackTable.NoHeader();
	trackTable.Enable(false);
	trackTable.SetFrame(InsetFrame());
	Add(trackTable.VSizePos(24, 0).HSizePos());

	PopulateDemoRows();
}

void TrackListPane::BuildToolbar() {
	trackToolbar.Clear();
	trackToolbar.Add("Presets", THISBACK(PopulateDemoRows));
	trackToolbar.Add("Edit In-Place", THISBACK(PopulateDemoRows));
	trackToolbar.Add("Mute All", THISBACK(PopulateDemoRows));
	trackToolbar.Add("Deactivate Solos", THISBACK(PopulateDemoRows));
	trackToolbar.Add("Read All", THISBACK(PopulateDemoRows));
	trackToolbar.Add("Write All", THISBACK(PopulateDemoRows));
	trackToolbar.Add("Track Colors", THISBACK(PopulateDemoRows));
}

void TrackListPane::PopulateDemoRows() {
	trackTable.Clear();
	trackTable.Add("Instrument 01", "M S R W", "Preset: Studio Strings");
	trackTable.Add("Audio 01", "M S R W", "Stereo");
	trackTable.Add("MIDI 01", "M S R W", "Drum Map: GM");
}

void TrackListPane::SetTracks(const Vector<String>& tracks) {
	trackTable.Clear();
	for(const String& track : tracks)
		trackTable.Add(track, "M S R W", "");
}

void TrackListPane::SetToolbarEnabled(bool enabled) {
	trackToolbar.Enable(enabled);
}

void TrackListPane::Clear() {
	trackTable.Clear();
}

void TrackListPane::AppendTrack(const String& name, const String& controls, const String& detail) {
	trackTable.Add(name, controls, detail);
}

ProjectAreaPane::ProjectAreaPane() {
	SetFrame(ThinInsetFrame());

	ruler.SetText("Bars+Beats");
	ruler.SetFrame(NullFrame());
	Add(ruler.TopPos(4, 20).HSizePos(4, 4));

	formatLabel.SetText("Format: Bars+Beats");
	Add(formatLabel.TopPos(24, 20).HSizePos(4, 4));

	horizontalZoom.MinMax(1, 200);
	horizontalZoom.SetData(50);
	Add(horizontalZoom.BottomPos(4, 20).RightPos(40, 120));

	verticalZoom.MinMax(1, 200);
	verticalZoom.SetData(50);
	Add(verticalZoom.TopPos(48, 200).RightPos(4, 20));

	clipCanvas.SetFrame(ThinInsetFrame());
	clipCanvas.Color(Color(235, 235, 235));
	Add(clipCanvas.VSizePos(48, 28).HSizePos(4, 28));
}

void ProjectAreaPane::SetRulerFormat(const String& format) {
	ruler.SetText(format);
	formatLabel.SetText("Format: " + format);
}

void ProjectAreaPane::SetZoomState(int horizontal, int vertical) {
	horizontalZoom.SetData(horizontal);
	verticalZoom.SetData(vertical);
}

void ProjectAreaPane::RefreshClips() {
	clipCanvas.Refresh();
}

ProjectWindowCtrl::ProjectWindowCtrl() {
	SetFrame(NullFrame());
	InitDefaultLayout();
}

void ProjectWindowCtrl::InitDefaultLayout() {
	Add(toolbar.TopPos(0, TOOLBAR_HEIGHT).HSizePos());
	Add(infoLine.TopPos(TOOLBAR_HEIGHT, ProjectInfoLinePane::INFO_HEIGHT).HSizePos());
	Add(horizontalSplit.VSizePos(HEADER_HEIGHT, 0).HSizePos());

	horizontalSplit << inspector << middleSplit;
	middleSplit << trackList << projectArea;

	ConfigureSplitters();
	InitDemoData();
}

void ProjectWindowCtrl::ConfigureSplitters() {
	horizontalSplit.SetPos(0, 1500);
	middleSplit.SetPos(0, 2200);
}

void ProjectWindowCtrl::InitDemoData() {
	toolbar.SetProjectTitle("Untitled Project");
	infoLine.ShowMidiColumns();
	Vector<ValueMap> demoPanels;
	ValueMap controls;
	controls("title") = "Track Controls";
	demoPanels.Add(controls);
	ValueMap inserts;
	inserts("title") = "MIDI Inserts";
	demoPanels.Add(inserts);
	ValueMap notes;
	notes("title") = "Notepad";
	demoPanels.Add(notes);
	UpdateInspectorPanels(demoPanels, "Instrument Track");

	Vector<ValueMap> demoTracks;
	ValueMap trackA;
	trackA("title") = "Instrument 01";
	trackA("controls") = "M S R W";
	trackA("detail") = "Preset: Studio Strings";
	demoTracks.Add(trackA);
	ValueMap trackB;
	trackB("title") = "Audio 01";
	trackB("controls") = "M S R W";
	trackB("detail") = "Stereo";
	demoTracks.Add(trackB);
	UpdateTrackList(demoTracks);

	ValueMap workState;
	workState("rulerFormat") = String("Bars+Beats");
	workState("zoomHorizontal") = 50;
	workState("zoomVertical") = 50;
	UpdateWorkAreaState(workState);
}

void ProjectWindowCtrl::SetProjectTitle(const String& title) {
	toolbar.SetProjectTitle(title);
}

void ProjectWindowCtrl::BindTimelineModel(Callback whenTimelineChanged) {
	onTimelineChanged = pick(whenTimelineChanged);
}

void ProjectWindowCtrl::BindTrackModel(Callback whenTrackModelChanged) {
	onTrackModelChanged = pick(whenTrackModelChanged);
}

void ProjectWindowCtrl::BindInspectorSource(Callback whenInspectorChanged) {
	onInspectorChanged = pick(whenInspectorChanged);
}

void ProjectWindowCtrl::SetProjectZoomState(int horizontal, int vertical) {
	projectArea.SetZoomState(horizontal, vertical);
}

void ProjectWindowCtrl::UpdateTrackList(const Vector<ValueMap>& entries) {
	cachedTrackEntries <<= entries;
	trackList.Clear();
	for(const ValueMap& row : cachedTrackEntries) {
		String title = const_cast<ValueMap&>(row).Get("title", "Unnamed Track");
		String controls = const_cast<ValueMap&>(row).Get("controls", "M S R W");
		String detail = const_cast<ValueMap&>(row).Get("detail", "");
		trackList.AppendTrack(title, controls, detail);
	}
	trackList.Refresh();
}

void ProjectWindowCtrl::UpdateInspectorPanels(const Vector<ValueMap>& panels, const String& caption) {
	cachedInspectorPanels <<= panels;
	inspector.SetTrackType(caption);
	inspector.SetPanels(cachedInspectorPanels);
	inspector.RefreshPanels();
}

void ProjectWindowCtrl::UpdateWorkAreaState(const ValueMap& state) {
	cachedWorkArea = state;
	String format = const_cast<ValueMap&>(cachedWorkArea).Get("rulerFormat", String("Bars+Beats"));
	projectArea.SetRulerFormat(format);
	if(cachedWorkArea.Find("zoomHorizontal") >= 0 && cachedWorkArea.Find("zoomVertical") >= 0)
		projectArea.SetZoomState((int)const_cast<ValueMap&>(cachedWorkArea).Get("zoomHorizontal", 0), (int)const_cast<ValueMap&>(cachedWorkArea).Get("zoomVertical", 0));
	projectArea.RefreshClips();
}

ProjectWindowHost::ProjectWindowHost() {
	Title("Project Window");
	Sizeable().Zoomable();
	Add(view.SizePos());
	view.SetProjectTitle("Untitled Project");
}

ProjectWindowCtrl& ProjectWindowHost::GetView() {
	return view;
}

void ProjectWindowHost::OpenProjectWindow() {
	Open();
}

void ProjectWindowHost::CloseProjectWindow() {
	Close();
}

void ProjectWindowHost::SetProjectTitle(const String& title) {
	view.SetProjectTitle(title);
	Title(title);
}

}
