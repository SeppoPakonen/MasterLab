#ifndef _AudioMaster_Views_h_
#define _AudioMaster_Views_h_

#include <CtrlLib/CtrlLib.h>
#include "../AudioUI/PostView.h"
#include "../AudioUI/PostGraphView.h"

using namespace Upp;

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
	
private:
	am::ui::PostView postView;
	void InitLayout();
};

class PostGraphViewWrapper : public Ctrl {
public:
	PostGraphViewWrapper();
	
private:
	am::ui::PostGraphView postGraphView;
	void InitLayout();
};

#endif