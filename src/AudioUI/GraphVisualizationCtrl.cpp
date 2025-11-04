#include "GraphVisualizationCtrl.h"

namespace am {
namespace UI {

GraphVisualizationCtrl::GraphVisualizationCtrl() : autoLayoutEnabled(true), layoutDirty(true) {
    Init();
}

GraphVisualizationCtrl::~GraphVisualizationCtrl() {
    // Cleanup
}

void GraphVisualizationCtrl::Init() {
    // Initialize the graph visualization control
    AddFrame(BlackFrame());
    nodePositions.Clear();
    activePath.Clear();
    highlightedNodes.Clear();
    highlightedEdges.Clear();
}

void GraphVisualizationCtrl::SetGraph(const PluginSDK::GraphVisualization& graph_) {
    // Since PluginSDK::GraphVisualization has move-only members, we need to copy manually
    graph.nodes.Clear();
    graph.edges.Clear();
    
    for(const auto& node : graph_.nodes) {
        graph.nodes.Add(node);
    }
    
    for(const auto& edge : graph_.edges) {
        graph.edges.Add(edge);
    }
    
    layoutDirty = true;
    Refresh();
}

void GraphVisualizationCtrl::SetActivePath(const Vector<String>& nodePath) {
    activePath.Clear();
    for(const auto& item : nodePath) {
        activePath.Add(item);
    }
    Refresh();
}

void GraphVisualizationCtrl::SetHighlightedNodes(const Vector<String>& nodeIds) {
    highlightedNodes.Clear();
    for(const auto& item : nodeIds) {
        highlightedNodes.Add(item);
    }
    Refresh();
}

void GraphVisualizationCtrl::SetHighlightedEdges(const Vector<String>& edgeIds) {
    highlightedEdges.Clear();
    for(const auto& item : edgeIds) {
        highlightedEdges.Add(item);
    }
    Refresh();
}

void GraphVisualizationCtrl::SetNodePositions(const VectorMap<String, Point>& positions) {
    nodePositions <<= positions;
    Refresh();
}

void GraphVisualizationCtrl::SetAutoLayoutEnabled(bool enabled) {
    autoLayoutEnabled = enabled;
    if (enabled) {
        layoutDirty = true;
        Refresh();
    }
}

void GraphVisualizationCtrl::LayoutNodes() {
    if (!autoLayoutEnabled) return;
    
    CalculateNodePositions();
}

void GraphVisualizationCtrl::CalculateNodePositions() {
    nodePositions.Clear();
    
    // Simple horizontal layout - could be enhanced with more sophisticated algorithms
    int nodeWidth = 120;
    int nodeHeight = 60;
    int spacing = 200;
    
    // For now, we'll arrange nodes in a simple horizontal layout
    // In a real implementation, we'd use a proper graph layout algorithm
    for (int i = 0; i < graph.nodes.GetCount(); i++) {
        const auto& node = graph.nodes[i];
        Point pos;
        pos.x = 50 + i * spacing;
        pos.y = 100;
        nodePositions.Add(node.id, pos);
    }
    
    layoutDirty = false;
}

void GraphVisualizationCtrl::Paint(Draw& draw) {
    // Draw background
    draw.DrawRect(GetSize(), SColorPaper());
    
    if (layoutDirty) {
        LayoutNodes();
    }
    
    // Draw edges first (so they appear behind nodes)
    for (int i = 0; i < graph.edges.GetCount(); i++) {
        const auto& edge = graph.edges[i];
        
        Point fromPos, toPos;
        if (nodePositions.Find(edge.from) && nodePositions.Find(edge.to)) {
            fromPos = nodePositions.Get(edge.from);
            toPos = nodePositions.Get(edge.to);
            
            int highlightedEdgeIndex = -1;
            for(int i = 0; i < highlightedEdges.GetCount(); i++) {
                if(highlightedEdges[i] == edge.from + "->" + edge.to) {
                    highlightedEdgeIndex = i;
                    break;
                }
            }
            bool isHighlighted = highlightedEdgeIndex >= 0;
            
            int activeFromIndex = -1, activeToIndex = -1;
            for(int i = 0; i < activePath.GetCount(); i++) {
                if(activePath[i] == edge.from) activeFromIndex = i;
                if(activePath[i] == edge.to) activeToIndex = i;
            }
            bool isActive = activeFromIndex >= 0 && activeToIndex >= 0;
            
            DrawEdge(draw, edge, fromPos, toPos, isHighlighted, isActive);
        }
    }
    
    // Draw nodes on top
    for (int i = 0; i < graph.nodes.GetCount(); i++) {
        const auto& node = graph.nodes[i];
        
        if (nodePositions.Find(node.id) >= 0) {
            Point pos = nodePositions.Get(node.id);
            int highlightedNodeIndex = -1;
            for(int i = 0; i < highlightedNodes.GetCount(); i++) {
                if(highlightedNodes[i] == node.id) {
                    highlightedNodeIndex = i;
                    break;
                }
            }
            bool isHighlighted = highlightedNodeIndex >= 0;
            
            int activeNodeIndex = -1;
            for(int i = 0; i < activePath.GetCount(); i++) {
                if(activePath[i] == node.id) {
                    activeNodeIndex = i;
                    break;
                }
            }
            bool isActive = activeNodeIndex >= 0;
            
            DrawNode(draw, node, pos, isHighlighted || isActive);
        }
    }
}

void GraphVisualizationCtrl::DrawNode(Draw& draw, const PluginSDK::GraphNode& node, Point pos, bool highlighted) {
    int nodeWidth = 120;
    int nodeHeight = 60;
    
    Rect nodeRect = RectC(pos.x - nodeWidth/2, pos.y - nodeHeight/2, nodeWidth, nodeHeight);
    
    // Draw node background
    Color bgColor = highlighted ? LtBlue() : SColorFace();
    draw.DrawRect(nodeRect, bgColor);
    
    // Draw node border
    Color borderColor = highlighted ? Blue() : Gray();
    draw.DrawLine(nodeRect.left, nodeRect.top, nodeRect.right, nodeRect.top, 2, borderColor); // top
    draw.DrawLine(nodeRect.left, nodeRect.bottom-1, nodeRect.right, nodeRect.bottom-1, 2, borderColor); // bottom
    draw.DrawLine(nodeRect.left, nodeRect.top, nodeRect.left, nodeRect.bottom, 2, borderColor); // left
    draw.DrawLine(nodeRect.right-1, nodeRect.top, nodeRect.right-1, nodeRect.bottom, 2, borderColor); // right
    
    // Draw node label
    String label = node.label;
    if (label.IsEmpty()) label = node.id;  // Use ID if no label
    
    draw.DrawText(nodeRect.left + 10, nodeRect.top + 20, label, StdFont(12), Black());
    
    // Draw group info if available
    if (!node.group.IsEmpty()) {
        draw.DrawText(nodeRect.left + 10, nodeRect.top + 40, node.group, StdFont(10), Gray());
    }
}

void GraphVisualizationCtrl::DrawEdge(Draw& draw, const PluginSDK::GraphEdge& edge, Point fromPos, Point toPos, 
                                      bool highlighted, bool active) {
    // Draw the connection line
    Color lineColor = active ? Red() : (highlighted ? Blue() : Gray());
    int lineWidth = active ? 3 : (highlighted ? 2 : 1);
    
    draw.DrawLine(fromPos.x, fromPos.y, toPos.x, toPos.y, lineWidth, lineColor);
    
    // Draw arrowhead
    double angle = atan2(toPos.y - fromPos.y, toPos.x - fromPos.x);
    double arrowSize = 8;
    
    Point arrow1, arrow2;
    arrow1.x = toPos.x - arrowSize * cos(angle - M_PI/6);
    arrow1.y = toPos.y - arrowSize * sin(angle - M_PI/6);
    arrow2.x = toPos.x - arrowSize * cos(angle + M_PI/6);
    arrow2.y = toPos.y - arrowSize * sin(angle + M_PI/6);
    
    draw.DrawLine(toPos.x, toPos.y, arrow1.x, arrow1.y, lineWidth, lineColor);
    draw.DrawLine(toPos.x, toPos.y, arrow2.x, arrow2.y, lineWidth, lineColor);
    
    // Draw edge label if needed
    if (edge.audio || edge.control) {
        Point midPoint;
        midPoint.x = (fromPos.x + toPos.x) / 2;
        midPoint.y = (fromPos.y + toPos.y) / 2;
        
        String label;
        if (edge.audio && edge.control) {
            label = "A+U";
        } else if (edge.audio) {
            label = "AUD";
        } else if (edge.control) {
            label = "CTL";
        }
        
        if (!label.IsEmpty()) {
            draw.DrawText(midPoint.x, midPoint.y, label, StdFont(10), lineColor);
        }
    }
}

void GraphVisualizationCtrl::MouseMove(Point p, dword keyflags) {
    mousePos = p;
    Ctrl::MouseMove(p, keyflags);
}

bool GraphVisualizationCtrl::Key(dword key, int count) {
    // Handle keyboard shortcuts for navigation, selection, etc.
    switch(key) {
        case K_LEFT:
        case K_RIGHT:
            // Could implement panning functionality
            break;
        default:
            return Ctrl::Key(key, count);
    }
    return true;
}

}  // namespace UI
}  // namespace am