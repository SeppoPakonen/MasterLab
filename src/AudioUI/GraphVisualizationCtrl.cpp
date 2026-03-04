#include "GraphVisualizationCtrl.h"
#include <Core/Core.h> // For M_PI
#include <CtrlLib/CtrlLib.h> // For StdFont, BlackFrame, etc.

namespace am {
namespace UI {

GraphVisualizationCtrl::GraphVisualizationCtrl()
{
	SetFrame(BlackFrame());
	SetWantFocus();
	
	// Init(); // No longer needed after members added
	lastMousePos = Pointf(0,0); // Initialize as Pointf
	draggingNode = false;
	draggedNodeId = "";
}

GraphVisualizationCtrl::~GraphVisualizationCtrl()
{
	
}

void GraphVisualizationCtrl::SetGraph(const PluginSDK::GraphVisualization& graph_)
{
	graph = graph_;
	layoutDirty = true;
	Refresh();
}

void GraphVisualizationCtrl::SetActivePath(const Vector<String>& path)
{
	activePath = path;
	Refresh();
}

void GraphVisualizationCtrl::SetNodeMapping(const VectorMap<String, String>& mapping)
{
	nodeMapping = mapping;
	Refresh();
}

void GraphVisualizationCtrl::SetNodePosition(const String& nodeId, Point pos)
{
	nodePositions.GetAdd(nodeId) = pos;
	Refresh();
}

void GraphVisualizationCtrl::AutoLayout()
{
	// Placeholder for auto-layout logic
	// For now, just assign random positions for demonstration
	if (graph.GetNodes().IsEmpty()) return;
	
	Size sz = GetSize();
	srand(0); // for reproducible random layout
	for (const auto& node : graph.GetNodes()) {
		nodePositions.GetAdd(node.id) = Point(rand() % (sz.cx - 100) + 50, rand() % (sz.cy - 100) + 50);
	}
	layoutDirty = false;
	Refresh();
}

void GraphVisualizationCtrl::RefreshLayout()
{
	if (autoLayoutEnabled || layoutDirty) {
		AutoLayout();
	}
	Refresh();
}

void GraphVisualizationCtrl::ClearHighlighting()
{
	highlightedNodes.Clear();
	highlightedEdges.Clear();
	Refresh();
}

void GraphVisualizationCtrl::SetHighlightedNodes(const Vector<String>& nodeIds)
{
	highlightedNodes = nodeIds; // Correct usage, Vector's assignment operator works
	Refresh();
}

void GraphVisualizationCtrl::SetHighlightedEdges(const Vector<String>& edgeIds)
{
	highlightedEdges = edgeIds; // Correct usage, Vector's assignment operator works
	Refresh();
}

void GraphVisualizationCtrl::Paint(Draw& draw)
{
	Size sz = GetSize();
	draw.DrawRect(sz, SColorPaper());
	
	if (layoutDirty) {
		AutoLayout();
	}

	// Draw edges
	for (const auto& edge : graph.GetEdges()) {
		if (nodePositions.Find(edge.sourceId) && nodePositions.Find(edge.targetId)) {
			Point from = nodePositions.Get(edge.sourceId);
			Point to = nodePositions.Get(edge.targetId);
			
			bool highlight = highlightedEdges.Find(edge.id) >= 0; // Use Find and check result
			DrawEdge(draw, edge, from, to, highlight);
		}
	}

	// Draw nodes
	for (const auto& node : graph.GetNodes()) {
		if (nodePositions.Find(node.id)) {
			Point pos = nodePositions.Get(node.id);
			bool highlight = highlightedNodes.Find(node.id) >= 0; // Use Find and check result
			DrawNode(draw, node, pos, highlight);
		}
	}
}

void GraphVisualizationCtrl::DrawNode(Draw& draw, const PluginSDK::GraphNode& node, Point pos, bool highlighted)
{
	Size nodeSize(80, 30);
	Rect r = Rect(pos.x - nodeSize.cx / 2, pos.y - nodeSize.cy / 2, nodeSize.cx, nodeSize.cy);
	
	draw.DrawRect(r, highlighted ? Blue() : LtGray());
	draw.DrawRect(r, 1, Black()); // Simple frame instead of DrawFatFrame
	draw.DrawText(r.CenterPoint().x - GetTextSize(node.name, StdFont()).cx / 2, r.CenterPoint().y - GetTextSize(node.name, StdFont()).cy / 2, node.name, StdFont(), Black());
}

void GraphVisualizationCtrl::DrawEdge(Draw& draw, const PluginSDK::GraphEdge& edge, Point fromPos, Point toPos, bool highlighted, bool active)
{
	draw.DrawLine(fromPos, toPos, 1, highlighted ? Red() : Black());
	// Draw arrow head
	Pointf dir = Pointf(toPos) - Pointf(fromPos); // Correct Point to Pointf conversion
	double angle = atan2(dir.y, dir.x);
	double arrowLen = 10;
	Pointf p1 = Pointf(toPos) + Pointf(arrowLen * cos(angle + M_PI * 3 / 4), arrowLen * sin(angle + M_PI * 3 / 4));
	Pointf p2 = Pointf(toPos) + Pointf(arrowLen * cos(angle - M_PI * 3 / 4), arrowLen * sin(angle - M_PI * 3 / 4));
	draw.DrawLine(toPos, p1, 1, highlighted ? Red() : Black());
	draw.DrawLine(toPos, p2, 1, highlighted ? Red() : Black());
}

void GraphVisualizationCtrl::LeftDown(Point p, dword keyflags)
{
	SetFocus();
	lastMousePos = Pointf(p); // Convert Point to Pointf
	for (const auto& node : graph.GetNodes()) {
		if (nodePositions.Find(node.id) && Rect(nodePositions.Get(node.id).x - 40, nodePositions.Get(node.id).y - 15, 80, 30).Contains(p)) {
			draggingNode = true;
			draggedNodeId = node.id;
			break;
		}
	}
	Ctrl::LeftDown(p, keyflags);
}

void GraphVisualizationCtrl::LeftUp(Point p, dword keyflags)
{
	draggingNode = false;
	draggedNodeId = "";
	Ctrl::LeftUp(p, keyflags);
}

void GraphVisualizationCtrl::MouseMove(Point p, dword keyflags)
{
	if (draggingNode && !draggedNodeId.IsEmpty()) {
		Pointf currentMousePos = Pointf(p); // Convert Point to Pointf
		Pointf delta = currentMousePos - lastMousePos;
		nodePositions.Get(draggedNodeId).x += (int)delta.x; // Apply delta, convert back to int for Point
		nodePositions.Get(draggedNodeId).y += (int)delta.y;
		lastMousePos = currentMousePos;
		Refresh();
	}
	Ctrl::MouseMove(p, keyflags);
}

bool GraphVisualizationCtrl::Key(dword key, int count)
{
	if (key == K_DELETE && !draggedNodeId.IsEmpty()) {
		// Placeholder for node deletion logic
		draggedNodeId = "";
		Refresh();
		return true;
	}
	return Ctrl::Key(key, count);
}

} // namespace UI
} // namespace am
