#ifndef _MIDI_CuteMidiEditView_h_
#define _MIDI_CuteMidiEditView_h_

class CuteMidiEditor;
class CuteMidiSequence;

class CuteMidiEditView : public ParentCtrl {
public:
    typedef CuteMidiEditView CLASSNAME;

    CuteMidiEditView();
    void SetEditor(CuteMidiEditor* editor);
    CuteMidiEditor* GetEditor() const;
    void SetSequence(CuteMidiSequence* sequence);
    CuteMidiSequence* GetSequence() const;

private:
    CuteMidiEditor* editor = nullptr;
    CuteMidiSequence* sequence = nullptr;
};

#endif
