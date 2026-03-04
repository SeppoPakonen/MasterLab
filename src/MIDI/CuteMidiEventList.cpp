#include "MIDI.h"

class CuteMidiEventListView : public ArrayCtrl {
public:
    CuteMidiEventListView() {
        AddColumn("Time");
        AddColumn("Type");
        AddColumn("Value");
    }
};

class CuteMidiEventList : public TopWindow {
public:
    typedef CuteMidiEventList CLASSNAME;

    CuteMidiEventList() {
        Title("Cute MIDI Events");
        Add(list.SizePos());
        SetRect(0, 0, 420, 300);
    }

private:
    CuteMidiEventListView list;
};
