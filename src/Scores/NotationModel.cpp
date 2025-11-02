#include "Scores.h"
namespace am {

NotationModel::NotationModel() {
	// Initialize with empty model
}

void NotationModel::AddMeasure(const Measure& measure) {
	// For now, we'll create a default measure since we can't copy the Measure due to deleted copy constructor
	// In a real implementation, this would need to be redesigned
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