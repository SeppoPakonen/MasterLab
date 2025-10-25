#ifndef _AudioUI_GraphEditorWidgets_h_
#define _AudioUI_GraphEditorWidgets_h_

#include <CtrlLib/CtrlLib.h>
// Note: Requires AudioGraph/Node.h and AudioGraph/Edge.h - included via main header in .cpp files

namespace am::ui {
using namespace Upp;
struct NodeWidget : Ctrl { Node* node = nullptr; };
struct EdgeWidget : Ctrl { Edge* edge = nullptr; };
}

#endif
namespace am::ui {
using namespace Upp;
struct NodeWidget : Ctrl { Node* node = nullptr; };
struct EdgeWidget : Ctrl { Edge* edge = nullptr; };
}