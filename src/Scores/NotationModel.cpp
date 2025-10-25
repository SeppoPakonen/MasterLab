#include "Scores.h"
namespace am {

NotationModel::NotationModel() {
	// Initialize with empty model
}

void NotationModel::AddMeasure(const Measure& measure) {
	measures.Add(measure);
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