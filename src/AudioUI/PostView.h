#ifndef _AudioUI_PostView_h_
#define _AudioUI_PostView_h_

// Note: Requires AudioGraph/AudioGraph.h - included via main header in .cpp files

namespace am::ui {
using namespace Upp;
struct PostView : ParentCtrl {
    PostGraph* post = nullptr; // not owned
    void SetPost(PostGraph* p) { post = p; Refresh(); }
    PostView();
};
}

#endif