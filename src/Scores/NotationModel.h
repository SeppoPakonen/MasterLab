#ifndef _Scores_NotationModel_h_
#define _Scores_NotationModel_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct Note : public Upp::Moveable<Note> {
	int pitch;  // MIDI note number
	double start_time;
	double duration;
	bool is_rest = false;
	
	// Add explicit constructors for U++ compatibility
	Note() = default;
	Note(const Note& other) = delete;
	Note& operator=(const Note& other) = delete;
	Note(Note&& other) = default;
	Note& operator=(Note&& other) = default;
	
	// Serialization support
	void Jsonize(JsonIO& jio) {
		jio
		("pitch", pitch)
		("start_time", start_time)
		("duration", duration)
		("is_rest", is_rest);
	}
};

struct Measure : public Upp::Moveable<Measure> {
	Upp::Vector<Note> notes;
	int time_signature_top = 4;
	int time_signature_bottom = 4;
	double tempo = 120.0;
	
	// Add explicit constructors for U++ compatibility
	Measure() = default;
	Measure(const Measure& other) = delete;
	Measure& operator=(const Measure& other) = delete;
	Measure(Measure&& other) = default;
	Measure& operator=(Measure&& other) = default;
	
	// Serialization support
	void Jsonize(JsonIO& jio) {
		jio
		("notes", notes)
		("time_signature_top", time_signature_top)
		("time_signature_bottom", time_signature_bottom)
		("tempo", tempo);
	}
};

class NotationModel {
public:
	NotationModel();
	void AddMeasure(const Measure& measure);
	void RemoveMeasure(int index);
	const Upp::Vector<Measure>& GetMeasures() const { return measures; }
	void Clear();
	
	// Serialization support
	void Jsonize(JsonIO& jio) {
		jio("measures", measures);
	}
	
private:
	Upp::Vector<Measure> measures;
};

}

#endif