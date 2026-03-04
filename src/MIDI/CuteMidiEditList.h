#ifndef _MIDI_CuteMidiEditList_h_
#define _MIDI_CuteMidiEditList_h_

class CuteMidiEditor;

class CuteMidiEditList : public ParentCtrl {
public:
    typedef CuteMidiEditList CLASSNAME;

    enum { ItemHeightMin = 4, ItemHeightBase = 8, ItemHeightMax = 32 };
    enum DragState { DragNone = 0, DragStart, DragMove, DragEnd };

    CuteMidiEditList();
    void SetEditor(CuteMidiEditor* editor);
    CuteMidiEditor* GetEditor() const;

private:
    CuteMidiEditor* editor = nullptr;
    ArrayCtrl list;
};

#endif
