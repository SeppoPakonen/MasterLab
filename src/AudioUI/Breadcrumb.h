#ifndef _AudioUI_Breadcrumb_h_
#define _AudioUI_Breadcrumb_h_

namespace am::ui {
using namespace Upp;
struct Breadcrumb : Ctrl {
    Upp::Vector<Upp::String> path;
    Event<int> WhenNavigate; // index in path
    void SetPath(const Upp::Vector<Upp::String>& p) { path <<= p; Refresh(); }
};
}

#endif