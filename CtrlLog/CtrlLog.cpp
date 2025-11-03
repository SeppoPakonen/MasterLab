#include "CtrlLog.h"

CtrlLog::CtrlLog()
{
    // Initialize the TreeCtrl for the log
    tree.AddColumn("Log Entries", 500);
    tree.WhenBar = callback(this, &CtrlLog::OnTreeBar);
    
    // Add a simple context menu option to clear the log
    tree.SetRoot("Log Entries", CtrlImg::smallright());
}

void CtrlLog::Log(const String& text)
{
    int pos = text.Find('\n');
    if (pos >= 0) {
        Log(text.Mid(0, pos));
        Log(text.Mid(pos + 1));
        return;
    }
    
    // Add new entry to the tree
    TreeCtrl::Node& n = tree.Add(CtrlImg::smallright(), text);
    tree.ScrollTo(n);
    
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
    tree.Clear();
    tree.SetRoot("Log Entries", CtrlImg::smallright());
}

void CtrlLog::TreeMenu(Bar& bar)
{
    bar.Add("Clear", CtrlImg::smallright(), THISBACK(Clear));
}

void CtrlLog::OnTreeBar(Bar& bar)
{
    TreeMenu(bar);
}