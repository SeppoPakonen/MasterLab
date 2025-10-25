#ifndef _AudioUI_Breadcrumb_h_
#define _AudioUI_Breadcrumb_h_

#include <CtrlLib/CtrlLib.h>

namespace am::ui {
using namespace Upp;
struct Breadcrumb : Ctrl {
    Vector<String> path;
    Event<int> WhenNavigate; // index in path
    void SetPath(const Vector<String>& p) { path = p; Refresh(); }
};
}

#endif
namespace am::ui {
using namespace Upp;
struct Breadcrumb : Ctrl {
    Vector<String> path;
    Event<int> WhenNavigate; // index in path
    void SetPath(const Vector<String>& p) { path = p; Refresh(); }
};
}