#ifndef _AudioMaster_MainWindow_h_
#define _AudioMaster_MainWindow_h_

#include <CtrlLib/CtrlLib.h>
#include "Views.h"

using namespace Upp;

enum ViewType { 
	MULTI_CHANNEL = 1, 
	MIXER = 2, 
	MASTERING = 0, 
	ANALYSIS = 3, 
	COMBINED = 4,
	POST = 5,
	POST_GRAPH = 6
};

class MainWindow : public ParentCtrl {
public:
	MainWindow();
	void SetView(int type);

private:
	void Menu(Bar& bar);
	void OnFile();
	void OnView();
	void OnSettings();
	void OnHelp();
	void OnMasteringView();
	void OnMultiChannelView();
	void OnMixerView();
	void OnAnalysisView();
	void OnCombinedView();
	void OnPostView();
	void OnPostGraphView();

	MenuBar menu;
	StatusBar status;
	WithSplitterFrame<ParentCtrl> viewContainer;
	Ctrl *currentView;
	
	// View instances
	Ctrl *masteringView;
	Ctrl *multiChannelView;
	Ctrl *mixerView;
	Ctrl *analysisView;
	Ctrl *combinedView;
	Ctrl *postView;
	Ctrl *postGraphView;
};

#endif