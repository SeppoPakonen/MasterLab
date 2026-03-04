#ifndef _MIDI_CuteMidiEventList_h_
#define _MIDI_CuteMidiEventList_h_

class CuteMidiEditor;
class CuteMidiSequence;
class CuteMidiEvent;

class CuteMidiEventListView : public ArrayCtrl {
public:
    typedef CuteMidiEventListView CLASSNAME;

    CuteMidiEventListView();
    void SetSequence(CuteMidiSequence* sequence);
    CuteMidiSequence* GetSequence() const;

private:
    CuteMidiSequence* sequence = nullptr;
};

class CuteMidiEventList : public TopWindow {
public:
    typedef CuteMidiEventList CLASSNAME;

    CuteMidiEventList();
    void SetEditor(CuteMidiEditor* editor);
    CuteMidiEditor* GetEditor() const;

private:
    CuteMidiEditor* editor = nullptr;
    CuteMidiEventListView list_view;
};

#endif
