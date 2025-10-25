#include "AudioMaster.h"  // This includes all necessary headers including AudioUI/AudioUI.h

void MainView::SetLabel(String s) {
	SubWindowCtrl::Title(s);
}

MultiChannelView::MultiChannelView() {
	InitLayout();
}

void MultiChannelView::InitLayout() {
	SetLabel("Multi-Channel View");
	
}

MixerView::MixerView() {
	InitLayout();
}

void MixerView::InitLayout() {
	SetLabel("Mixer View");
	
}

MasteringView::MasteringView() {
	InitLayout();
}

void MasteringView::InitLayout() {
	SetLabel("Mastering View");
	
}

AnalysisView::AnalysisView() {
	InitLayout();
}

void AnalysisView::InitLayout() {
	SetLabel("Analysis View");
	
}

CombinedView::CombinedView() {
	InitLayout();
}

void CombinedView::InitLayout() {
	SetLabel("Combined View");
	
	// Create a vertical splitter: MultiChannelView above, MixerView below
	topView.win = win;
	bottomView.win = win;
	
	splitter.Vert(topView, bottomView);
	splitter.SetPos(6666);
	
	Add(splitter.SizePos());
}

PostViewWrapper::PostViewWrapper() {
	InitLayout();
}

PostViewWrapper::~PostViewWrapper() {
	
}

void PostViewWrapper::InitLayout() {
	SetLabel("Post View");
	
	// Initialize the post view
	Add(postView.SizePos());
}

PostGraphViewWrapper::PostGraphViewWrapper() {
	InitLayout();
}

PostGraphViewWrapper::~PostGraphViewWrapper() {
	
}

void PostGraphViewWrapper::InitLayout() {
	SetLabel("Post Graph View");
	
	// Initialize the post graph view
	Add(postGraphView.SizePos());
	
}