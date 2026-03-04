#ifndef _MIDI_CuteMidiControlForm_h_
#define _MIDI_CuteMidiControlForm_h_

class CuteMidiControlTypeGroup;

class CuteMidiControlForm : public TopWindow {
public:
    typedef CuteMidiControlForm CLASSNAME;

    CuteMidiControlForm();
    void SetControl(const CuteMidiControl::MapVal& map_val);
    CuteMidiControl::MapVal GetControl() const;

private:
    DropList control_type;
    EditInt control_channel;
    DropList control_param;
    Option logarithmic;
    Option inverted;
    Option bipolar;
    Button ok_button;
    Button cancel_button;
};

#endif
