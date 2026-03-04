#ifndef _MIDI_CuteMidiSysexForm_h_
#define _MIDI_CuteMidiSysexForm_h_

class CuteMidiSysexList;

class CuteMidiSysexForm : public TopWindow {
public:
    typedef CuteMidiSysexForm CLASSNAME;
    CuteMidiSysexForm();
    void SetSysexList(CuteMidiSysexList* sysex_list);
    CuteMidiSysexList* GetSysexList() const;
private:
    CuteMidiSysexList* sysex_list = nullptr;
    ArrayCtrl list;
    Button ok_button;
    Button cancel_button;
};

#endif
