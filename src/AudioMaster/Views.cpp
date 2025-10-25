#include "Views.h"

MultiChannelView::MultiChannelView() {
	InitLayout();
}

void MultiChannelView::InitLayout() {
	SetLabel("Multi-Channel View");
	AddFrame(StaticRect(Color(220, 220, 255)));
	Label *label = new Label();
	label->SetText("Multi-Channel View Placeholder");
	AddChild(label);
}

MixerView::MixerView() {
	InitLayout();
}

void MixerView::InitLayout() {
	SetLabel("Mixer View");
	AddFrame(StaticRect(Color(255, 220, 220)));
	Label *label = new Label();
	label->SetText("Mixer View Placeholder");
	AddChild(label);
}

MasteringView::MasteringView() {
	InitLayout();
}

void MasteringView::InitLayout() {
	SetLabel("Mastering View");
	AddFrame(StaticRect(Color(220, 255, 220)));
	Label *label = new Label();
	label->SetText("Mastering View Placeholder");
	AddChild(label);
}

AnalysisView::AnalysisView() {
	InitLayout();
}

void AnalysisView::InitLayout() {
	SetLabel("Analysis View");
	AddFrame(StaticRect(Color(255, 255, 220)));
	Label *label = new Label();
	label->SetText("Analysis View Placeholder");
	AddChild(label);
}

CombinedView::CombinedView() {
	InitLayout();
}

void CombinedView::InitLayout() {
	SetLabel("Combined View");
	AddFrame(StaticRect(Color(220, 255, 255)));
	
	// Create a vertical splitter: MultiChannelView above, MixerView below
	WithSplitterFrame<ParentCtrl> *splitter = new WithSplitterFrame<ParentCtrl>();
	
	MultiChannelView *topView = new MultiChannelView();
	MixerView *bottomView = new MixerView();
	
	splitter->Horz(*topView, *bottomView);
	AddChild(splitter);
}

PostViewWrapper::PostViewWrapper() {
	InitLayout();
}

void PostViewWrapper::InitLayout() {
	SetLabel("Post View");
	AddFrame(StaticRect(Color(255, 220, 255)));
	
	// Initialize the post view
	AddChild(&postView);
}

PostGraphViewWrapper::PostGraphViewWrapper() {
	InitLayout();
}

void PostGraphViewWrapper::InitLayout() {
	SetLabel("Post Graph View");
	AddFrame(StaticRect(Color(220, 255, 255)));
	
	// Initialize the post graph view
	AddChild(&postGraphView);
}