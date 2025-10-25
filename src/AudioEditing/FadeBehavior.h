#ifndef _AudioEditing_FadeBehavior_h_
#define _AudioEditing_FadeBehavior_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct FadeBehavior {
	bool handlesAlwaysOnTop = true;
	bool thickFadeLines = false;
	bool showFadeCurves = true;
	
	// Fade shape preferences
	enum class FadeShape {
		Crossfade,
		Linear,
		Logarithmic,
		Exponential
	} defaultShape = FadeShape::Crossfade;
};

class FadeBehaviorManager {
public:
	FadeBehaviorManager();
	
	const FadeBehavior& GetBehavior() const { return behavior; }
	void SetBehavior(const FadeBehavior& newBehavior);
	
	// Apply fade behavior to audio events
	void ApplyToEvents();
	
private:
	FadeBehavior behavior;
};

}

#endif