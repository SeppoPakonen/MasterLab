#ifndef _AudioGraph_Node_h_
#define _AudioGraph_Node_h_

#include <Core/Core.h>
// Note: Requires AudioFX/AudioFX.h and Port.h - included via main header in .cpp files

namespace am {
	
struct Effect; // Forward declaration
struct Port; // Forward declaration for same package

struct Node : Pte<Node> {
    Upp::String label;
    Ptr<Effect> effect;     // optional: effect processor hosted by node
    Upp::Vector<Port> inputs;
    Upp::Vector<Port> outputs;
    virtual ~Node(){}
    virtual bool IsContainer() const { return false; }
};

}

#endif