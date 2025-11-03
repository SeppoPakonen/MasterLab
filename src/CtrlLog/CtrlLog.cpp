#include "CtrlLog.h"

CtrlLog::CtrlLog()
{
    // Initialize the RichTextCtrl
    Add(editor.HSizePos().VSizePos());
    
    logText = "Log Entries:\n";
    editor <<= logText;
}

void CtrlLog::Log(const String& text)
{
    String current = ~editor;
    if (!current.EndsWith("\n") && !current.IsEmpty()) {
        current << "\n";
    }
    current << text;
    
    // Update the editor
    editor <<= current;
    
    // Call any registered callback
    if(on_log)
        on_log(text);
}

void CtrlLog::Log(const char* text)
{
    Log(String(text));
}

void CtrlLog::Clear()
{
    logText = "Log Entries:\n";
    editor <<= logText;
}

void CtrlLog::Menu(Bar& bar)
{
    bar.Add("Clear", CtrlImg::smallright(), callback(this, &CtrlLog::Clear));
}