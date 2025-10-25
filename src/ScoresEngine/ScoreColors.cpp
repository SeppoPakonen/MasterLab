#include "ScoresEngine.h"
namespace am {

ScoreColors::ScoreColors() {
	// Initialize with default color rules
	ScoreColorRule rule1;
	rule1.event = "note";
	rule1.active = true;
	rule1.color = Black();
	colorRules.Add(rule1);
	
	ScoreColorRule rule2;
	rule2.event = "rest";
	rule2.active = true;
	rule2.color = Blue();
	colorRules.Add(rule2);
	
	ScoreColorRule rule3;
	rule3.event = "clef";
	rule3.active = true;
	rule3.color = Green();
	colorRules.Add(rule3);
}

void ScoreColors::AddColorRule(const ScoreColorRule& rule) {
	colorRules.Add(rule);
}

void ScoreColors::RemoveColorRule(int index) {
	if (index >= 0 && index < colorRules.GetCount()) {
		colorRules.Remove(index);
	}
}

void ScoreColors::ClearColorRules() {
	colorRules.Clear();
}

Color ScoreColors::GetColorForEvent(const String& event) const {
	for (const auto& rule : colorRules) {
		if (rule.event == event && rule.active) {
			return rule.color;
		}
	}
	// Return black as default color if no rule matches
	return Black();
}

void ScoreColors::ApplyToScoreDisplay() {
	LOG("Applying score colors to display");
	for (const auto& rule : colorRules) {
		LOG("Event: " + rule.event + ", Color: " + AsString(rule.color) + ", Active: " + (rule.active ? "yes" : "no"));
	}
}

}