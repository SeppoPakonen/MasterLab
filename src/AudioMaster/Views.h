#ifndef _AudioMaster_Views_h_
#define _AudioMaster_Views_h_

// Note: This header uses types from AudioUI/AudioUI.h - full types available 
// when implementation files include AudioMaster/AudioMaster.h

using namespace Upp;

namespace am::ui {
    struct PostView;      // Forward declaration
    struct PostGraphView; // Forward declaration
}

class MainWindow;


class MainView : public SubWindowCtrl {
public:
	virtual void InitLayout() = 0;
	void SetLabel(String s);
	
	MainWindow* win = 0;
	
};

class MultiChannelView : public MainView {
public:
	MultiChannelView();
	
private:
	void InitLayout() override;
};

class MixerView : public MainView {
public:
	MixerView();
	
private:
	void InitLayout() override;
};

class MasteringView : public MainView {
public:
	MasteringView();
	
private:
	void InitLayout() override;
};

class AnalysisView : public MainView {
public:
	AnalysisView();
	
private:
	void InitLayout() override;
};

class CombinedView : public MainView {
public:
	CombinedView();
	
	Splitter splitter;
	MultiChannelView topView;
	MixerView bottomView;
	
private:
	void InitLayout() override;
};

class PostViewWrapper : public MainView {
public:
	PostViewWrapper();
	~PostViewWrapper();
	
private:
	am::ui::PostView postView; // Pointer to avoid needing full definition in header
	void InitLayout() override;
};

class PostGraphViewWrapper : public MainView {
public:
	PostGraphViewWrapper();
	~PostGraphViewWrapper();
	
private:
	am::ui::PostGraphView postGraphView; // Pointer to avoid needing full definition in header
	void InitLayout() override;
};

#endif