#include "AudioMaster.h"

CuteMainForm* CuteMainForm::instance = nullptr;

CuteMainForm::CuteMainForm() {
    instance = this;
    Title("Cute");
    Add(status_label.BottomPos(0, 24).HSizePos());
    Add(workspace.VSizePos(0, 24).HSizePos());
}
CuteMainForm::~CuteMainForm() { if(instance == this) instance = nullptr; }
CuteMainForm* CuteMainForm::GetInstance() { return instance; }
void CuteMainForm::Setup() { status_label.SetText("Ready"); }
void CuteMainForm::ClearFilename() { filename.Clear(); }
void CuteMainForm::UpdateTransportTime(unsigned long play_head) { status_label.SetText(AsString(play_head)); }
void CuteMainForm::AppendMessages(const String& text) { if(messages) messages->AppendMessage(text); }
void CuteMainForm::AppendMessagesError(const String& text) { if(messages) messages->AppendMessage("Error: " + text); }
CuteFileSystem* CuteMainForm::GetFileSystem() const { return file_system; }
CuteFiles* CuteMainForm::GetFiles() const { return files; }
CuteConnections* CuteMainForm::GetConnections() const { return connections; }
