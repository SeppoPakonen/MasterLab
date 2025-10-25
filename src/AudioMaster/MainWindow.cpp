#include "AudioMaster.h"

MainWindow::MainWindow() {
	Sizeable().Zoomable();
	
	// Initialize status bar
	AddFrame(status);
	status.SetText("AudioMaster - Ready");
	
	// Initialize view container
	AddFrame(menu);
	Add(viewContainer.SizePos());
	
	// Create view instances
	masteringView = new MasteringView();
	multiChannelView = new MultiChannelView();
	mixerView = new MixerView();
	analysisView = new AnalysisView();
	combinedView = new CombinedView();
	postView = new PostViewWrapper();
	postGraphView = new PostGraphViewWrapper();
	
	currentView = NULL;
	
	// Set default view
	SetView(0); // Default to Mastering view
}

void MainWindow::SetView(int type) {
	// Remove current view if exists
	if(currentView) {
		viewContainer.Remove(*currentView);
	}
	
	// Select the new view
	switch(type) {
		case 0: // Mastering view
			currentView = masteringView;
			break;
		case 1: // Multi-channel view
			currentView = multiChannelView;
			break;
		case 2: // Mixer view
			currentView = mixerView;
			break;
		case 3: // Analysis view
			currentView = analysisView;
			break;
		case 4: // Combined view
			currentView = combinedView;
			break;
		case 5: // Post view
			currentView = postView;
			break;
		case 6: // Post graph view
			currentView = postGraphView;
			break;
		default:
			currentView = masteringView;
			break;
	}
	
	// Add the new view to container
	if(currentView) {
		viewContainer.Add(*currentView);
	}
}

void MainWindow::Menu(Bar& bar) {
	bar.Add("File", THISBACK(OnFile));
	bar.Add("View", THISBACK(OnView));
	bar.Add("Settings", THISBACK(OnSettings));
	bar.Add("Help", THISBACK(OnHelp));
}

void MainWindow::OnView() {
	MenuBar vbar;
	vbar.Add("Mastering", CtrlImg::newdir(), THISBACK(OnMasteringView));
	vbar.Add("Multi-Channel", CtrlImg::file(), THISBACK(OnMultiChannelView));
	vbar.Add("Mixer", CtrlImg::copy(), THISBACK(OnMixerView));
	vbar.Add("Analysis", CtrlImg::paste(), THISBACK(OnAnalysisView));
	vbar.Add("Combined", CtrlImg::deletefile(), THISBACK(OnCombinedView));
	vbar.AddSeparator();
	vbar.Add("Post", CtrlImg::newdir(), THISBACK(OnPostView));
	vbar.Add("Post Graph", CtrlImg::file(), THISBACK(OnPostGraphView));
	Popup(vbar);
}

void MainWindow::OnFile() {
	PromptOK("File menu clicked");
}

void MainWindow::OnSettings() {
	PromptOK("Settings menu clicked");
}

void MainWindow::OnHelp() {
	PromptOK("Help menu clicked");
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