#include "AudioMaster.h"  // This includes all necessary headers including AudioUI/AudioUI.h

void MainView::SetLabel(Upp::String s) {
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
	
	// Initialize the post view - since it's a pointer, we need to create the instance
	// For now, comment out until we have proper implementation
	// Add(postView->SizePos());
}

PostGraphViewWrapper::PostGraphViewWrapper() {
	InitLayout();
}

PostGraphViewWrapper::~PostGraphViewWrapper() {
	
}

void PostGraphViewWrapper::InitLayout() {
	SetLabel("Post Graph View");
	
	// Initialize the post graph view - since it's a pointer, we need to create the instance
	// For now, comment out until we have proper implementation
	// Add(postGraphView->SizePos());
	
}

KeyEditorView::KeyEditorView() {
	InitLayout();
}

void KeyEditorView::InitLayout() {
	if(built)
		return;
	built = true;

	SetLabel("Key Editor Workspace");
	header.SetLabel("Key Editor Workspace - Piano Roll");
	header.SetFrame(InsetFrame());
	Add(header.TopPos(0, 24).HSizePos());

	noteGrid.AddColumn("Pitch");
	noteGrid.AddColumn("Position");
	noteGrid.AddColumn("Length");
	noteGrid.Add("C3", "1.1.1.0", "1/4");
	noteGrid.Add("E3", "1.1.2.0", "1/4");
	noteGrid.Add("G3", "1.1.3.0", "1/4");
	noteGrid.Add("B3", "1.1.4.0", "1/4");
	noteGrid.SetFrame(InsetFrame());
	Add(noteGrid.VSizePos(24, 0).HSizePos());
}

ScoreEditorView::ScoreEditorView() {
	InitLayout();
}

void ScoreEditorView::InitLayout() {
	if(built)
		return;
	built = true;

	SetLabel("Score Editor Workspace");
	header.SetLabel("Score Editor Workspace - Notation");
	header.SetFrame(InsetFrame());
	Add(header.TopPos(0, 24).HSizePos());

	symbolGrid.AddColumn("Bar");
	symbolGrid.AddColumn("Beat");
	symbolGrid.AddColumn("Symbol");
	symbolGrid.Add("1", "1", "Treble Clef");
	symbolGrid.Add("1", "1.5", "C4 Quarter");
	symbolGrid.Add("1", "2", "E4 Quarter");
	symbolGrid.Add("1", "2.5", "G4 Quarter");
	symbolGrid.SetFrame(InsetFrame());
	Add(symbolGrid.VSizePos(24, 0).HSizePos());
}
