#pragma once
#include <CtrlLib/CtrlLib.h>
#include "../AudioGraph/AudioGraph.h"  // Include main header of AudioGraph
namespace am::ui {
using namespace Upp;
struct PostView : ParentCtrl {
    PostGraph* post = nullptr; // not owned
    void SetPost(PostGraph* p) { post = p; Refresh(); }
    PostView();
};
}