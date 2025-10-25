#include <Core/Core.h>
#include "../src/AudioGraph/PostGraph.h"
#include "../src/AudioFX/Crossover.h"
#include "../src/AudioFX/Splitter.h"

CONSOLE_APP_MAIN {
    using namespace Upp;
    using namespace am;
    
    PostGraph graph;
    graph.BuildDefault();
    
    // Check that we can create a basic graph structure
    Crossover* crossover = new Crossover();
    Splitter* splitter = new Splitter();
    
    Node* crossNode = new Node();
    crossNode->effect = crossover;
    crossNode->label = "Crossover";
    
    Node* splitNode = new Node();
    splitNode->effect = splitter;
    splitNode->label = "Splitter";
    
    int crossId = graph.graph.AddNode(crossNode);
    int splitId = graph.graph.AddNode(splitNode);
    
    // Connect them
    MultiChannelLayout mcl;
    graph.graph.Connect(crossId, 0, splitId, 0, mcl);
    
    LOG("Graph topology test completed successfully");
}