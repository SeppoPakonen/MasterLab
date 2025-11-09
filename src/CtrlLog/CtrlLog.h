#ifndef _CtrlLog_CtrlLog_h_
#define _CtrlLog_CtrlLog_h_

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LAYOUTFILE <CtrlLog/CtrlLog.lay>
#include <CtrlCore/lay.h>

#define IMAGECLASS CtrlLogImg
#define IMAGEFILE <CtrlLog/CtrlLog.iml>
#include <Draw/iml.h>

struct CtrlLog : public ParentCtrl {
    CtrlLog();
    virtual void Log(const String& text);
    virtual void Log(const char* text);
    virtual void Clear();
    
private:
    void TreeMenu(Bar& bar);
    void OnTreeBar(Bar& bar);
    
    TreeCtrl tree;
    Callback1<String> on_log;
};

#endif