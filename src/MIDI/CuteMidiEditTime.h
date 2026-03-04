#ifndef _MIDI_CuteMidiEditTime_h_
#define _MIDI_CuteMidiEditTime_h_

class CuteMidiEditor;

class CuteMidiEditTime : public ParentCtrl {
public:
    typedef CuteMidiEditTime CLASSNAME;

    enum DragState { DragNone = 0, DragSeek, DragLoop, DragPunch };

    CuteMidiEditTime();
    void SetEditor(CuteMidiEditor* editor);
    CuteMidiEditor* GetEditor() const;
    void SetFrame(unsigned long frame);
    unsigned long GetFrame() const;

private:
    CuteMidiEditor* editor = nullptr;
    unsigned long frame = 0;
};

#endif
