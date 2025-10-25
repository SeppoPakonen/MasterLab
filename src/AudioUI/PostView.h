#pragma once
#include <CtrlLib/CtrlLib.h>
#include "../AudioGraph/PostGraph.h"
namespace am::ui {
using namespace Upp;
struct PostView : ParentCtrl {
    PostGraph* post = nullptr; // not owned
    void SetPost(PostGraph* p) { post = p; Refresh(); }
    PostView();
};
}