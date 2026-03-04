#include "MIDI.h"

CuteMidiEventListView::CuteMidiEventListView() {
    AddColumn("Time");
    AddColumn("Type");
    AddColumn("Value");
}

void CuteMidiEventListView::SetSequence(CuteMidiSequence* sequence) {
    this->sequence = sequence;
}

CuteMidiSequence* CuteMidiEventListView::GetSequence() const {
    return sequence;
}

CuteMidiEventList::CuteMidiEventList() {
    Title("Cute MIDI Events");
    Add(list_view.SizePos());
    SetRect(0, 0, 420, 300);
}

void CuteMidiEventList::SetEditor(CuteMidiEditor* editor) {
    this->editor = editor;
}

CuteMidiEditor* CuteMidiEventList::GetEditor() const {
    return editor;
}
