#include "PostGraphView.h"
namespace am::ui {
PostGraphView::PostGraphView() { Add(crumb.SizePosTop()); /* add canvas area etc. */ }
void PostGraphView::SetGraph(Graph* g) { graph = g; Refresh(); }
}