#ifndef _MIDI_CuteMidiControlObserverForm_h_
#define _MIDI_CuteMidiControlObserverForm_h_

class CuteMidiControlObserver;
class CuteMidiControlTypeGroup;

class CuteMidiControlObserverForm : public TopWindow {
public:
    typedef CuteMidiControlObserverForm CLASSNAME;

    CuteMidiControlObserverForm();
    void SetObserver(CuteMidiControlObserver* observer);
    CuteMidiControlObserver* GetObserver() const;

private:
    CuteMidiControlObserver* observer = nullptr;
    DropList control_type;
    EditInt channel;
    EditInt parameter;
    Button map_button;
    Button unmap_button;
};

#endif
