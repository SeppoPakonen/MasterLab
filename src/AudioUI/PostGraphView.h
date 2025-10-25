#pragma once
#include <CtrlLib/CtrlLib.h>
#include "../AudioGraph/Graph.h"
#include "Breadcrumb.h"
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