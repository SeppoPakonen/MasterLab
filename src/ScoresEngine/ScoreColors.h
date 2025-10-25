#ifndef _ScoresEngine_ScoreColors_h_
#define _ScoresEngine_ScoreColors_h_

#include <Draw/Draw.h>
#include <Core/Core.h>
using namespace Upp;

namespace am {

struct ScoreColorRule {
	String event;      // Type of event to color
	bool active;       // Whether this rule is active
	Color color;       // Color to use
};

class ScoreColors {
public:
	ScoreColors();
	
	// Color rule management
	void AddColorRule(const ScoreColorRule& rule);
	void RemoveColorRule(int index);
	void ClearColorRules();
	Vector<ScoreColorRule> GetColorRules() const { return colorRules; }
	void SetColorRules(const Vector<ScoreColorRule>& rules) { colorRules = rules; }
	
	// Get color for an event
	Color GetColorForEvent(const String& event) const;
	
	// Apply color settings to score display
	void ApplyToScoreDisplay();
	
private:
	Vector<ScoreColorRule> colorRules;
};

}

#endif