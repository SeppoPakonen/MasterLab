#include "CtrlLog.h"

CtrlLog::CtrlLog()
{
    // Add tree control to the CtrlLog
    Add(tree.SizePos());

    // Add the root node to the tree - corrected API usage
    tree.SetRoot(CtrlImg::smallright(), "Log Entries");
}

void CtrlLog::Log(const String& text)
{
    int pos = text.Find('\n');
    if (pos >= 0) {
        Log(text.Mid(0, pos));
        Log(text.Mid(pos + 1));
        return;
    }

    // Add new entry to the tree - corrected API usage
    int newNodeId = tree.Add(0, CtrlImg::smallright(), text);  // 0 is root ID
    // Select the new node - using correct method
    tree.Set(0, newNodeId, text);  // parent, node id, value

    // Scroll to the new item - using correct method
    tree.ScrollTo(Point(0, 0));  // Scroll to top-left position
}

void CtrlLog::Log(const char* text)
{
    Log(String(text));
}

void CtrlLog::Clear()
{
    tree.Clear();
    tree.SetRoot(CtrlImg::smallright(), "Log Entries");
}

void CtrlLog::TreeMenu(Bar& bar)
{
    bar.Add("Clear", CtrlImg::smallright(), [this]() { this->Clear(); });
}

void CtrlLog::OnTreeBar(Bar& bar)
{
    TreeMenu(bar);
}