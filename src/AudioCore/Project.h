#pragma once
#include "Timeline.h"
#include "Transport.h"
#include "Mixer.h"
namespace am {
struct Project {
    Timeline timeline;
    Transport transport;
    Mixer mixer;
    // later: asset registry, undo, session I/O
};
}