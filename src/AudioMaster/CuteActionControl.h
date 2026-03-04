#ifndef _AudioMaster_CuteActionControl_h_
#define _AudioMaster_CuteActionControl_h_

class CuteAction;
class CuteMenu;
class CuteMidiControlObserver;
class CuteSubject;

class CuteActionControl {
public:
	class MidiObserver;
	typedef VectorMap<String, MidiObserver*> MidiObserverMap;

	CuteActionControl();
	~CuteActionControl();

	const MidiObserverMap& GetMidiObservers() const;
	MidiObserver* GetMidiObserver(CuteAction* action);
	MidiObserver* AddMidiObserver(CuteAction* action);
	void RemoveMidiObserver(CuteAction* action);
	void Clear();

	static CuteActionControl* GetInstance();
	static String MenuActionText(CuteAction* action, const String& text);

	void Triggered(bool is_on);

	class MidiObserver : public CuteMidiControlObserver {
	public:
		MidiObserver(CuteAction* action);
		void Update(bool is_update);

	private:
		CuteAction* action;
		CuteSubject* subject;
	};

private:
	String GetActionId(CuteAction* action) const;

	MidiObserverMap midi_observers;
	static CuteActionControl* instance;
};

#endif
