#include "MIDI.h"

CuteMidiEditSelect::CuteMidiEditSelect() {}
void CuteMidiEditSelect::AddItem(CuteMidiEvent* event, const Rect& rect_event) { Item item; item.rect_event = rect_event; items.GetAdd((void*)event, item) = item; }
void CuteMidiEditSelect::RemoveItem(CuteMidiEvent* event) { int i = items.Find((void*)event); if(i >= 0) items.Remove(i); }
void CuteMidiEditSelect::Clear() { items.Clear(); }
const VectorMap<void*, CuteMidiEditSelect::Item>& CuteMidiEditSelect::GetItems() const { return items; }
