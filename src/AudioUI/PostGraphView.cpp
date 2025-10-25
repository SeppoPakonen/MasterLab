#include "AudioUI.h"
namespace am::ui {
	
PostGraphView::PostGraphView() { Add(crumb.SizePos()); /* add canvas area etc. */ }
void PostGraphView::SetGraph(Graph* g) { graph = g; Refresh(); }

}