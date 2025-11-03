#ifndef _CtrlLog_CtrlLog_h_
#define _CtrlLog_CtrlLog_h_

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

struct CtrlLog : public Ctrl {
    CtrlLog();
    virtual void Log(const String& text);
    virtual void Log(const char* text);
    virtual void Clear();
    
private:
    void Menu(Bar& bar);
    
    RichTextCtrl editor;  // Using RichTextCtrl for log display
    String logText;
    Callback1<String> on_log;
};

#endif