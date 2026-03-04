#ifndef _MIDI_CuteInstrumentMenu_h_
#define _MIDI_CuteInstrumentMenu_h_

class CuteTrack;
class CuteMidiManager;

class CuteInstrumentMenu : public ParentCtrl {
public:
    typedef CuteInstrumentMenu CLASSNAME;

    CuteInstrumentMenu();
    void SetTrack(CuteTrack* track);
    void SetMidiManager(CuteMidiManager* midi_manager);
    void Rebuild();

private:
    CuteTrack* track = nullptr;
    CuteMidiManager* midi_manager = nullptr;
    ArrayCtrl list;
};

#endif
