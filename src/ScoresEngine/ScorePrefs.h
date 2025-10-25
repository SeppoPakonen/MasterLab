#ifndef _ScoresEngine_ScorePrefs_h_
#define _ScoresEngine_ScorePrefs_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class ScorePrefs {
public:
	ScorePrefs();
	
	// Apply preferences to score system
	void ApplyToScores();
	
private:
	// Score-specific preferences would go here
};

}

#endif