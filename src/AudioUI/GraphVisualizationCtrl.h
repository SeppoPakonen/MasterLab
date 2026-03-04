#ifndef _AudioUI_GraphVisualizationCtrl_h_
#define _AudioUI_GraphVisualizationCtrl_h_

#include <CtrlLib/CtrlLib.h>
#include <PluginSDK/PluginTypes.h> // Explicitly include PluginTypes.h

namespace am {
namespace UI {

using namespace Upp;

class GraphVisualizationCtrl : public Ctrl {
public:
	typedef GraphVisualizationCtrl CLASSNAME;

	GraphVisualizationCtrl();

	void SetGraph(const PluginSDK::GraphVisualization& graph);
	void SetActivePath(const Vector<String>& path);
	void SetNodeMapping(const VectorMap<String, String>& mapping);
	void SetNodePosition(const String& node, Point pos);
	void AutoLayout();
	void RefreshLayout();

protected:
	virtual void Paint(Draw& draw) override;
	virtual void MouseMove(Point p, dword keyflags) override;
	virtual bool Key(dword key, int count) override;

private:
	void DrawNode(Draw& draw, const PluginSDK::GraphNode& node, Point pos, bool highlighted = false);
	void DrawEdge(Draw& draw, const PluginSDK::GraphEdge& edge, Point fromPos, Point toPos, bool highlighted = false, bool active = false);

	PluginSDK::GraphVisualization graph;
	Vector<String> activePath;
	VectorMap<String, String> nodeMapping;
	VectorMap<String, Point> nodePositions;
};

} // namespace UI
} // namespace am

#endif
