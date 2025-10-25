#ifndef _AudioCore_Project_h_
#define _AudioCore_Project_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {
	
struct Timeline; // Forward declaration - full type provided by main header
struct Transport; // Forward declaration - full type provided by main header
struct Mixer; // Forward declaration - full type provided by main header

struct Project {
    Timeline timeline;
    Transport transport;
    Mixer mixer;
    
    // New methods required by design
    void SetAutosave(bool on, double minutes, int maxBackups) {
        autosave_enabled = on;
        autosave_minutes = minutes;
        autosave_max_backups = maxBackups;
    }
    void SetMaxUndo(int n) { max_undo = n; }
    
    // Getters for new properties
    bool GetAutosaveEnabled() const { return autosave_enabled; }
    double GetAutosaveMinutes() const { return autosave_minutes; }
    int GetAutosaveMaxBackups() const { return autosave_max_backups; }
    int GetMaxUndo() const { return max_undo; }
    
    // New fields required by design
    // later: asset registry, undo, session I/O
private:
    bool autosave_enabled = true;
    double autosave_minutes = 15.0;
    int autosave_max_backups = 10;
    int max_undo = -1;  // -1 means infinite
};

}

#endif
