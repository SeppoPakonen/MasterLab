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
	bar.Add("View", THISBACK(OnView));
	bar.Add("Settings", THISBACK(OnSettings));
	bar.Add("Help", THISBACK(OnHelp));
}

void MainWindow::OnView(Bar& vbar) {
	vbar.Add("Mastering", CtrlImg::new_doc(), THISBACK(OnMasteringView));
	vbar.Add("Multi-Channel", CtrlImg::new_doc(), THISBACK(OnMultiChannelView));
	vbar.Add("Mixer", CtrlImg::copy(), THISBACK(OnMixerView));
	vbar.Add("Analysis", CtrlImg::paste(), THISBACK(OnAnalysisView));
	vbar.Add("Combined", CtrlImg::remove(), THISBACK(OnCombinedView));
	vbar.Separator();
	vbar.Add("Post", CtrlImg::new_doc(), THISBACK(OnPostView));
	vbar.Add("Post Graph", CtrlImg::new_doc(), THISBACK(OnPostGraphView));
}

void MainWindow::OnFile(Bar& bar) {
	// add: bar.Add(...
}

void MainWindow::OnSettings(Bar& bar) {
	// add: bar.Add(...
}

void MainWindow::OnHelp(Bar& bar) {
	// add: bar.Add(...
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