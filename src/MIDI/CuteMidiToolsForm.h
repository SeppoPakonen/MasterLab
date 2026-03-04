#ifndef _MIDI_CuteMidiToolsForm_h_
#define _MIDI_CuteMidiToolsForm_h_

class CuteMidiClip;
class CuteMidiEditSelect;
class CuteMidiEditCommand;
class CuteTimeScale;

class CuteMidiToolsForm : public TopWindow {
public:
    typedef CuteMidiToolsForm CLASSNAME;
    CuteMidiToolsForm();
    void SetClip(CuteMidiClip* clip);
    CuteMidiClip* GetClip() const;
private:
    CuteMidiClip* clip = nullptr;
    DropList tool_list;
    EditInt amount;
    Button apply_button;
    Button cancel_button;
};

#endif
