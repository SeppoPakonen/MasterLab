#ifndef _AudioMaster_MainWindow_h_
#define _AudioMaster_MainWindow_h_

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

class MainWindow : public TopWindow {
	String view_status;
	
public:
	typedef MainWindow CLASSNAME;
	MainWindow();
	void SetView(int type);
	void SetViewLabel(String s);
	void RefreshTitle();
	void InitView(MainView& v);
	
private:
	void Menu(Bar& bar);
	void OnFile(Bar& bar);
	void OnView(Bar& bar);
	void OnSettings(Bar& bar);
	void OnHelp(Bar& bar);
	void OnMasteringView();
	void OnMultiChannelView();
	void OnMixerView();
	void OnAnalysisView();
	void OnCombinedView();
	void OnPostView();
	void OnPostGraphView();

	MenuBar menu;
	StatusBar status;
	ParentCtrl viewContainer;
	Ptr<Ctrl> currentView;
	
	// View instances
	MasteringView masteringView;
	MultiChannelView multiChannelView;
	MixerView mixerView;
	AnalysisView analysisView;
	CombinedView combinedView;
	PostViewWrapper postView;
	PostGraphViewWrapper postGraphView;
};

#endif