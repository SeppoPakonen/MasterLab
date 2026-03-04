#include "AudioMaster.h"

class CuteAction {};
class CuteMidiControlObserver {
public:
	virtual ~CuteMidiControlObserver() {}
};
class CuteSubject {};

CuteActionControl* CuteActionControl::instance = nullptr;

CuteActionControl::MidiObserver::MidiObserver(CuteAction* action)
	: action(action), subject(nullptr) {
}

void CuteActionControl::MidiObserver::Update(bool is_update) {
	(void)is_update;
	// Phase 1 note: original behavior routed trigger events back into the bound UI action.
}

CuteActionControl::CuteActionControl() {
	instance = this;
}

CuteActionControl::~CuteActionControl() {
	Clear();
	instance = nullptr;
}

const CuteActionControl::MidiObserverMap& CuteActionControl::GetMidiObservers() const {
	return midi_observers;
}

String CuteActionControl::GetActionId(CuteAction* action) const {
	return AsString((void*)action);
}

CuteActionControl::MidiObserver* CuteActionControl::GetMidiObserver(CuteAction* action) {
	int index = midi_observers.Find(GetActionId(action));
	return index >= 0 ? midi_observers[index] : nullptr;
}

CuteActionControl::MidiObserver* CuteActionControl::AddMidiObserver(CuteAction* action) {
	String action_id = GetActionId(action);
	MidiObserver* observer = GetMidiObserver(action);
	if(!observer) {
		observer = new MidiObserver(action);
		midi_observers.Add(action_id, observer);
	}
	return observer;
}

void CuteActionControl::RemoveMidiObserver(CuteAction* action) {
	int index = midi_observers.Find(GetActionId(action));
	if(index >= 0) {
		delete midi_observers[index];
		midi_observers.Remove(index);
	}
}

void CuteActionControl::Clear() {
	for(int i = 0; i < midi_observers.GetCount(); i++)
		delete midi_observers[i];
	midi_observers.Clear();
}

CuteActionControl* CuteActionControl::GetInstance() {
	return instance;
}

String CuteActionControl::MenuActionText(CuteAction* action, const String& text) {
	(void)action;
	return text;
}

void CuteActionControl::Triggered(bool is_on) {
	(void)is_on;
	// Phase 1 note: original code toggled the MIDI observer value based on action checked-state.
}
