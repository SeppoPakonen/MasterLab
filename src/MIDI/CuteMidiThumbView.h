#ifndef _MIDI_CuteMidiThumbView_h_
#define _MIDI_CuteMidiThumbView_h_

class CuteMidiEditor;

class CuteMidiThumbView : public ParentCtrl {
public:
    typedef CuteMidiThumbView CLASSNAME;
    enum { DragNone = 0, DragStart, DragMove, DragClick };

    CuteMidiThumbView();
    void SetEditor(CuteMidiEditor* editor);
    CuteMidiEditor* GetEditor() const;

private:
    CuteMidiEditor* editor = nullptr;
    int drag_state = DragNone;
};

#endif
