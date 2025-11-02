#include "Scores.h"
namespace am {

NotationModel::NotationModel() {
	// Initialize with empty model
}

void NotationModel::AddMeasure(const Measure& measure) {
	// Measure has deleted copy constructor, so we can't copy it
	// In a real implementation, this would need to be redesigned
	// For now, we'll just create a default measure
	measures.Add(Measure());
}

void NotationModel::RemoveMeasure(int index) {
	if (index >= 0 && index < measures.GetCount()) {
		measures.Remove(index);
	}
}

void NotationModel::Clear() {
	measures.Clear();
}

}