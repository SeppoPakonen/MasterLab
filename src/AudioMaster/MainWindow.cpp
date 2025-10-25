#include "AudioMaster.h"

MainWindow::MainWindow() {
	Sizeable().Zoomable();
	RefreshTitle();
	
	// Initialize status bar
	AddFrame(status);
	status = "AudioMaster - Ready";
	
	// Initialize view container
	AddFrame(menu);
	Add(viewContainer.SizePos());
	
	// Create view instances
	InitView(masteringView);
	InitView(multiChannelView);
	InitView(mixerView);
	InitView(analysisView);
	InitView(combinedView);
	InitView(postView);
	InitView(postGraphView);
	
	currentView = NULL;
	
	// Set default view
	SetView(0); // Default to Mastering view
}

void MainWindow::InitView(MainView& v) {
	v.win = this;
}

void MainWindow::SetView(int type) {
	// Remove current view if exists
	if(currentView) {
		viewContainer.RemoveChild(currentView);
	}
	
	// Select the new view
	switch(type) {
		case 0: // Mastering view
			currentView = &masteringView;
			break;
		case 1: // Multi-channel view
			currentView = &multiChannelView;
			break;
		case 2: // Mixer view
			currentView = &mixerView;
			break;
		case 3: // Analysis view
			currentView = &analysisView;
			break;
		case 4: // Combined view
			currentView = &combinedView;
			break;
		case 5: // Post view
			currentView = &postView;
			break;
		case 6: // Post graph view
			currentView = &postGraphView;
			break;
		default:
			currentView = &masteringView;
			break;
	}
	
	// Add the new view to container
	if(currentView) {
		viewContainer.Add(*currentView);
	}
}

void MainWindow::SetViewLabel(String s) {
	view_status = s;
	RefreshTitle();
}

void MainWindow::RefreshTitle() {
	String s;
	s << "MasterLab";
	if (!view_status.IsEmpty())
		s << " :: " << view_status;
	SetTitle(s);
}

void MainWindow::Menu(Bar& bar) {
	bar.Add("File", THISBACK(OnFile));
	bar.Add("Edit", THISBACK(OnEdit));
	bar.Add("Project", THISBACK(OnProject));
	bar.Add("Audio", THISBACK(OnAudio));
	bar.Add("MIDI", THISBACK(OnMIDI));
	bar.Add("Scores", THISBACK(OnScores));
	bar.Add("Media", THISBACK(OnMedia));
	bar.Add("Transport", THISBACK(OnTransport));
	bar.Add("Devices", THISBACK(OnDevices));
	bar.Add("Window", THISBACK(OnWindow));
	bar.Add("Help", THISBACK(OnHelp));
}

void MainWindow::OnEdit(Bar& bar) {
	
}

void MainWindow::OnProject(Bar& bar) {
	
}

void MainWindow::OnAudio(Bar& bar) {
	
}

void MainWindow::OnMIDI(Bar& bar) {
	
}

void MainWindow::OnScores(Bar& bar) {
	
}

void MainWindow::OnMedia(Bar& bar) {
	
}

void MainWindow::OnTransport(Bar& bar) {
	
}

void MainWindow::OnDevices(Bar& bar) {
	
}

void MainWindow::OnWindow(Bar& bar) {
	
}

void MainWindow::OnHelp(Bar& bar) {
	
}

void MainWindow::OnMasteringView() {
	SetView(0);
}

void MainWindow::OnMultiChannelView() {
	SetView(1);
}

void MainWindow::OnMixerView() {
	SetView(2);
}

void MainWindow::OnAnalysisView() {
	SetView(3);
}

void MainWindow::OnCombinedView() {
	SetView(4);
}

void MainWindow::OnPostView() {
	SetView(5);
}

void MainWindow::OnPostGraphView() {
	SetView(6);
}