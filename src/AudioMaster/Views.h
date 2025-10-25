#ifndef _AudioMaster_Views_h_
#define _AudioMaster_Views_h_

#include <CtrlLib/CtrlLib.h>

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

#endif