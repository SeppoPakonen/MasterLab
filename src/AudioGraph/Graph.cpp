#include "AudioGraph.h"
namespace am {
int Graph::AddNode(Node* n) {
    int index = nodes.GetCount();
    nodes.Add(n);
    return index;
}

void Graph::Connect(int fromNode, int fromPort, int toNode, int toPort, const MultiChannelLayout& mcl) {
    if (fromNode >= 0 && fromNode < nodes.GetCount() && 
        toNode >= 0 && toNode < nodes.GetCount()) {
        Edge edge;
        edge.from = &nodes[fromNode];
        edge.from_port = fromPort;
        edge.to = &nodes[toNode];
        edge.to_port = toPort;
        edge.layout = mcl;
        edges.Add(edge);
    }
}
}