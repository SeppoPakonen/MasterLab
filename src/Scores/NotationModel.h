#ifndef _Scores_NotationModel_h_
#define _Scores_NotationModel_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct Note {
	int pitch;  // MIDI note number
	double start_time;
	double duration;
	bool is_rest = false;
};

struct Measure {
	Vector<Note> notes;
	int time_signature_top = 4;
	int time_signature_bottom = 4;
	double tempo = 120.0;
};

class NotationModel {
public:
	NotationModel();
	void AddMeasure(const Measure& measure);
	void RemoveMeasure(int index);
	const Vector<Measure>& GetMeasures() const { return measures; }
	void Clear();
	
private:
	Vector<Measure> measures;
};

}

#endif