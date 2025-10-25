#ifndef _AudioMaster_Views_h_
#define _AudioMaster_Views_h_

#include <CtrlLib/CtrlLib.h>
// Note: This header uses types from AudioUI/AudioUI.h - full types available 
// when implementation files include AudioMaster/AudioMaster.h

using namespace Upp;

namespace am::ui {
    struct PostView;      // Forward declaration
    struct PostGraphView; // Forward declaration
}

class MultiChannelView : public Ctrl {
public:
	MultiChannelView();
	
private:
	void InitLayout();
};

class MixerView : public Ctrl {
public:
	MixerView();
	
private:
	void InitLayout();
};

class MasteringView : public Ctrl {
public:
	MasteringView();
	
private:
	void InitLayout();
};

class AnalysisView : public Ctrl {
public:
	AnalysisView();
	
private:
	void InitLayout();
};

class CombinedView : public Ctrl {
public:
	CombinedView();
	
private:
	void InitLayout();
};

class PostViewWrapper : public Ctrl {
public:
	PostViewWrapper();
	~PostViewWrapper();
	
private:
	am::ui::PostView* postView; // Pointer to avoid needing full definition in header
	void InitLayout();
};

class PostGraphViewWrapper : public Ctrl {
public:
	PostGraphViewWrapper();
	~PostGraphViewWrapper();
	
private:
	am::ui::PostGraphView* postGraphView; // Pointer to avoid needing full definition in header
	void InitLayout();
};

#endif