#ifndef _ScoresEngine_ScoreColors_h_
#define _ScoresEngine_ScoreColors_h_

#include <Draw/Draw.h>
#include <Core/Core.h>
using namespace Upp;

namespace am {

struct ScoreColorRule : public Moveable<ScoreColorRule> {
	Upp::String event;      // Type of event to color
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
	const Upp::Vector<ScoreColorRule>& GetColorRules() const { return colorRules; }
	void SetColorRules(const Upp::Vector<ScoreColorRule>& rules) { colorRules <<= rules; }
	
	// Get color for an event
	Color GetColorForEvent(const Upp::String& event) const;
	
	// Apply color settings to score display
	void ApplyToScoreDisplay();
	
private:
	Upp::Vector<ScoreColorRule> colorRules;
};

}

#endif