#include "AudioMaster.h"

CuteMessages::CuteMessages() {
    Title("Cute Messages");
    Add(text.SizePos());
}
void CuteMessages::AppendMessage(const String& text_value) {
    String current = text.GetQTF();
    if(!current.IsEmpty())
        current << '\n';
    current << text_value;
    text.SetQTF(current);
}
void CuteMessages::SetMessagesLimit(int messages_limit) { this->messages_limit = messages_limit; }
int CuteMessages::GetMessagesLimit() const { return messages_limit; }
void CuteMessages::Clear() { text.Clear(); }
