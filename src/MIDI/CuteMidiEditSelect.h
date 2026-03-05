#ifndef _MIDI_CuteMidiEditSelect_h_
#define _MIDI_CuteMidiEditSelect_h_

class CuteMidiEditSelect {
public:
    struct Item : Moveable<Item> {
        Rect rect_event;
        unsigned int flags = 1;
    };

    CuteMidiEditSelect();
    void AddItem(CuteMidiEvent* event, const Rect& rect_event);
    void RemoveItem(CuteMidiEvent* event);
    void Clear();
    const VectorMap<void*, Item>& GetItems() const;

private:
    VectorMap<void*, Item> items;
};

#endif
