#include "AudioEditing.h"
namespace am {

FadeBehaviorManager::FadeBehaviorManager() {
	// Initialize with default fade behavior
	behavior.handlesAlwaysOnTop = true;
	behavior.thickFadeLines = false;
	behavior.showFadeCurves = true;
	behavior.defaultShape = FadeBehavior::FadeShape::Crossfade;
}

void FadeBehaviorManager::SetBehavior(const FadeBehavior& newBehavior) {
	behavior = newBehavior;
}

void FadeBehaviorManager::ApplyToEvents() {
	LOG("Applying fade behavior");
	LOG("Handles always on top: " << (behavior.handlesAlwaysOnTop ? "yes" : "no"));
	LOG("Thick fade lines: " << (behavior.thickFadeLines ? "yes" : "no"));
	LOG("Show fade curves: " << (behavior.showFadeCurves ? "yes" : "no"));
	
	String shapeStr;
	switch (behavior.defaultShape) {
		case FadeBehavior::FadeShape::Crossfade: shapeStr = "Crossfade"; break;
		case FadeBehavior::FadeShape::Linear: shapeStr = "Linear"; break;
		case FadeBehavior::FadeShape::Logarithmic: shapeStr = "Logarithmic"; break;
		case FadeBehavior::FadeShape::Exponential: shapeStr = "Exponential"; break;
	}
	LOG("Default fade shape: " + shapeStr);
}

}