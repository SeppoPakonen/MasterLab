#include "MediaPool.h"

namespace {

class PoolSearchDialog : public TopWindow {
public:
	typedef PoolSearchDialog CLASSNAME;
	PoolSearchDialog();

private:
	void BuildLayout();

	DropList scopeDrop;
	Button searchButton;
	Button selectButton;
	Button playButton;
	Button stopButton;
	Button pauseButton;
	Button repeatButton;
	SliderCtrl volumeSlider;
	SliderCtrl positionSlider;
	Option autoplayOption;
	EditString queryField;
	ArrayCtrl resultList;
};

PoolSearchDialog::PoolSearchDialog() {
	Title("Media Pool Search");
	Size(Size(640, 360));
	MinimizeBox(false);
	MaximizeBox(false);
	BuildLayout();
}

void PoolSearchDialog::BuildLayout() {
	scopeDrop.Add("Search Pool");
	scopeDrop.Add("[Hard Disks]");
	scopeDrop.Add("Select Search Path...");
	scopeDrop.SetIndex(0);
	Label scopeLabel;
	scopeLabel.SetText("Scope:");
	Add(scopeLabel.TopPos(8, 20).LeftPos(8, 80));
	Add(scopeDrop.TopPos(8, 20).LeftPos(96, 200));

	searchButton.SetLabel("Search");
	selectButton.SetLabel("Select");
	Add(searchButton.TopPos(8, 24).RightPos(120, 100));
	Add(selectButton.TopPos(8, 24).RightPos(12, 100));

	Label queryLabel;
	queryLabel.SetText("Query:");
	Add(queryLabel.TopPos(40, 20).LeftPos(8, 80));
	Add(queryField.TopPos(40, 20).LeftPos(96, 240));

	playButton.SetLabel("Play");
	stopButton.SetLabel("Stop");
	pauseButton.SetLabel("Pause");
	repeatButton.SetLabel("Repeat");
	Add(playButton.TopPos(72, 24).LeftPos(8, 80));
	Add(stopButton.TopPos(72, 24).LeftPos(92, 80));
	Add(pauseButton.TopPos(72, 24).LeftPos(176, 80));
	Add(repeatButton.TopPos(72, 24).LeftPos(260, 80));

	volumeSlider.Vertical();
	volumeSlider.MinMax(0, 100);
	volumeSlider.SetData(80);
	Add(volumeSlider.TopPos(40, 112).LeftPos(320, 20));

	positionSlider.MinMax(0, 1000);
	positionSlider.SetData(0);
	Add(positionSlider.TopPos(104, 20).HSizePos(360, 12));

	autoplayOption.SetLabel("Autoplay");
	Add(autoplayOption.TopPos(136, 20).LeftPos(8, 120));

	resultList.AddColumn("Name");
	resultList.AddColumn("Length");
	resultList.AddColumn("Sample Rate");
	resultList.AddColumn("Bits");
	resultList.AddColumn("Channels");
	resultList.AddColumn("Date & Time");
	resultList.AddColumn("Size");
	resultList.AddColumn("Path");
	resultList.Add("Kick Loop", "0:00:01.200", "44.1 kHz", "24", "Stereo", "2025-10-26", "1.2 MB", "Audio/Kick Loop.wav");
	Add(resultList.VSizePos(168, 8).HSizePos(8, 8));
}

}

namespace am {

PoolWindow::PoolWindow() {
	Init();
}

void PoolWindow::Init() {
	Title("Media Pool");
	Size(Size(960, 600));
	Sizeable().Zoomable();

	BuildToolbar();
	BuildList();

	Add(statusBar.BottomPos(0, 24).HSizePos());
	UpdateStatusText();
	ToggleStatusBar(statusVisible);
}

void PoolWindow::BuildToolbar() {
	toolbar.SetFrame(ThinInsetFrame());
	Add(toolbar.TopPos(0, 32).HSizePos());

	toggleStatusBarButton.SetLabel("Status Bar");
	toggleStatusBarButton.WhenAction = THISBACK(OnToggleStatusBar);
	toolbar.Add(toggleStatusBarButton, 100);

	playButton.SetLabel("Play Selected");
	playButton.WhenAction = THISBACK(OnPlaySelected);
	toolbar.Add(playButton, 120);

	loopButton.SetLabel("Loop");
	loopButton.WhenAction = THISBACK(OnLoopSelected);
	toolbar.Add(loopButton, 70);

	toolbarVolume.Vertical();
	toolbarVolume.MinMax(0, 100);
	toolbarVolume.SetData(80);
	toolbar.Add(toolbarVolume, 36);

	columnVisibility.Add("Column Visibility");
	columnVisibility.Add("Minimal");
	columnVisibility.Add("Metadata Heavy");
	columnVisibility.SetIndex(0);
	toolbar.Add(columnVisibility, 160);

	openAllButton.SetLabel("Open All");
	openAllButton.WhenAction = THISBACK(OnOpenAll);
	toolbar.Add(openAllButton, 100);

	closeAllButton.SetLabel("Close All");
	closeAllButton.WhenAction = THISBACK(OnCloseAll);
	toolbar.Add(closeAllButton, 100);

	importButton.SetLabel("Import...");
	importButton.WhenAction = THISBACK(OnImportMedia);
	toolbar.Add(importButton, 100);

	searchButton.SetLabel("Search...");
	searchButton.WhenAction = THISBACK(OnSearchMedia);
	toolbar.Add(searchButton, 100);

	projectFolderLabel.SetText("Project Folder: Projects/Demo");
	poolFolderLabel.SetText("Pool Record Folder: Media/Audio");
	toolbar.Add(projectFolderLabel, 220);
	toolbar.Add(poolFolderLabel, 220);
}

void PoolWindow::BuildList() {
	mediaList.AddColumn("Media");
	mediaList.AddColumn("Used");
	mediaList.AddColumn("Status");
	mediaList.AddColumn("Musical Mode");
	mediaList.AddColumn("Tempo");
	mediaList.AddColumn("Signature");
	mediaList.AddColumn("Key");
	mediaList.AddColumn("Algorithm");
	mediaList.AddColumn("Info");
	mediaList.AddColumn("Type");
	mediaList.AddColumn("Date");
	mediaList.AddColumn("Origin Time");
	mediaList.AddColumn("Waveform");
	mediaList.AddColumn("Path");
	mediaList.AddColumn("Reel Name");

	mediaList.Add("Amanda", 1, "", false, "120 BPM", "4/4", "C", "MIX", "44.1 kHz, 24-bit, Stereo", "Wave", "2025-10-26", "1.01.01.000", "(wave)", "Audio/Amanda.wav", "");
	mediaList.Add("Bassline", 2, "", true, "124 BPM", "4/4", "Gm", "Solo", "48 kHz, 24-bit, Stereo", "Wave", "2025-10-25", "1.02.00.000", "(wave)", "Audio/Bassline.wav", "Reel 1");

	Add(mediaList.VSizePos(32, statusVisible ? 24 : 0).HSizePos());
}

void PoolWindow::OpenWindow() {
	Open();
	Activate();
}

void PoolWindow::CloseWindow() {
	Close();
}

void PoolWindow::RefreshList() {
	UpdateStatusText();
	mediaList.Refresh();
}

void PoolWindow::ToggleStatusBar(bool show) {
	statusVisible = show;
	statusBar.Show(statusVisible);
	mediaList.VSizePos(32, statusVisible ? 24 : 0);
	toggleStatusBarButton.SetLabel(statusVisible ? "Hide Status Bar" : "Show Status Bar");
	Layout();
}

void PoolWindow::UpdateStatusText() {
	String text;
	text << mediaList.GetCount() << " media files in Pool; "
		 << mediaList.GetCount() << " used in Project; total size 62.19 MB; external files: 0";
	statusBar = text;
}

void PoolWindow::OnToggleStatusBar() {
	ToggleStatusBar(!statusVisible);
}

void PoolWindow::OnPlaySelected() {
	// Placeholder: hook into audition engine
}

void PoolWindow::OnLoopSelected() {
	// Placeholder for loop audition toggle
}

void PoolWindow::OnImportMedia() {
	// Placeholder: forward to Import subsystem
}

void PoolWindow::OnSearchMedia() {
	PoolSearchDialog dlg;
	dlg.Run();
}

void PoolWindow::OnOpenAll() {
	// Placeholder for expanding trees
}

void PoolWindow::OnCloseAll() {
	// Placeholder for collapsing trees
}

}
