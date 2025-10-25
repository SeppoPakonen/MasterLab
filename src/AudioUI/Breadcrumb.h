#pragma once
#include <CtrlLib/CtrlLib.h>
namespace am::ui {
using namespace Upp;
struct Breadcrumb : Ctrl {
    Vector<String> path;
    Event<int> WhenNavigate; // index in path
    void SetPath(const Vector<String>& p) { path = p; Refresh(); }
};
}