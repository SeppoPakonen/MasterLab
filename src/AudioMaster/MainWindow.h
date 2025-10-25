#ifndef _AudioMaster_MainWindow_h_
#define _AudioMaster_MainWindow_h_

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

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
};

#endif