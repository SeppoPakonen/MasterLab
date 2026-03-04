#ifndef _MIDI_CuteMidiControlTypeGroup_h_
#define _MIDI_CuteMidiControlTypeGroup_h_

class CuteMidiControlTypeGroup : public ParentCtrl {
public:
    typedef CuteMidiControlTypeGroup CLASSNAME;

    CuteMidiControlTypeGroup();
    void SetControlType(int control_type);
    int GetControlType() const;

private:
    DropList type_list;
    int control_type = 0;
};

#endif
