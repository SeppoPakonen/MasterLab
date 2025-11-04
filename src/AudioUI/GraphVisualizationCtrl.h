#ifndef _AudioUI_GraphVisualizationCtrl_h_
#define _AudioUI_GraphVisualizationCtrl_h_

#include <CtrlLib/CtrlLib.h>
#include <AudioCore/AudioCore.h>
#include <AudioFX/AudioFX.h>
#include <PluginSDK/PluginSDK.h>
using namespace Upp;

namespace am {
namespace UI {

// Control for visualizing processing graphs with nodes and edges
class GraphVisualizationCtrl : public Ctrl {
public:
	typedef GraphVisualizationCtrl CLASSNAME;
	
	GraphVisualizationCtrl();
	virtual ~GraphVisualizationCtrl();
	
	// Set the graph data to visualize
	void SetGraph(const PluginSDK::GraphVisualization& graph);
	
	// Update active path visualization
	void SetActivePath(const Vector<String>& nodePath);
	
	// Set highlighting for specific nodes/edges
	void SetHighlightedNodes(const Vector<String>& nodeIds);
	void SetHighlightedEdges(const Vector<String>& edgeIds);
	
	// Set node positions (if auto-layout is disabled)
	void SetNodePositions(const VectorMap<String, Point>& positions);
	
	// Enable/disable auto-layout
	void SetAutoLayoutEnabled(bool enabled);
	
protected:
	virtual void Paint(Draw& draw) override;
	virtual void MouseMove(Point p, dword keyflags) override;
	virtual bool Key(dword key, int count) override;
	
private:
	void Init();
	void LayoutNodes();
	void CalculateNodePositions();
	void DrawNode(Draw& draw, const PluginSDK::GraphNode& node, Point pos, bool highlighted = false);
	void DrawEdge(Draw& draw, const PluginSDK::GraphEdge& edge, Point fromPos, Point toPos, bool highlighted = false, bool active = false);
	
	// Graph visualization data
	PluginSDK::GraphVisualization graph;
	Vector<String> activePath;
	Vector<String> highlightedNodes;
	Vector<String> highlightedEdges;
	VectorMap<String, Point> nodePositions;
	bool autoLayoutEnabled;
	
	// UI interaction state
	Point mousePos;
	bool layoutDirty;
};

}  // namespace UI
}  // namespace am

#endif