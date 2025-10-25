#ifndef _AudioCore_Project_h_
#define _AudioCore_Project_h_

namespace am {
struct Timeline; // Forward declaration - full type provided by main header
struct Transport; // Forward declaration - full type provided by main header
struct Mixer; // Forward declaration - full type provided by main header
struct Project {
    Timeline timeline;
    Transport transport;
    Mixer mixer;
    // later: asset registry, undo, session I/O
};
}

#endif