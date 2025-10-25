#ifndef _AudioUI_PostGraphView_h_
#define _AudioUI_PostGraphView_h_

// Note: Requires AudioGraph/AudioGraph.h and Breadcrumb.h - included via main header in .cpp files

namespace am::ui {
	
using namespace Upp;
struct PostGraphView : ParentCtrl {
    Graph* graph = nullptr; // current graph at this depth
    Breadcrumb crumb;
    Callback2<int,int> WhenNodeDoubleClick; // (nodeIndex, button)
    void SetGraph(Graph* g);
    PostGraphView();
};

}

#endif