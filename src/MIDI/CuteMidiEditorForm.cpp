#include "MIDI.h"

CuteMidiEditorForm::CuteMidiEditorForm() {
    Title("Cute MIDI Editor");
    Add(menu_bar.TopPos(0, 24).HSizePos());
    Add(tool_bar.TopPos(24, 28).HSizePos());
    Add(workspace.VSizePos(52, 24).HSizePos());
    Add(status_bar.BottomPos(0, 24).HSizePos());
    SetRect(0, 0, 900, 600);
}
void CuteMidiEditorForm::SetEditor(CuteMidiEditor* editor) { this->editor = editor; }
CuteMidiEditor* CuteMidiEditorForm::GetEditor() const { return editor; }
