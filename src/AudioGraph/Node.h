#pragma once
#include <Core/Core.h>
#include <AudioFX/AudioFX.h>  // Use main header instead
#include "Port.h"
namespace am {
struct Node {
    String label;
    Ptr<Effect> effect;     // optional: effect processor hosted by node
    Vector<Port> inputs;
    Vector<Port> outputs;
    virtual ~Node(){}
    virtual bool IsContainer() const { return false; }
};
}