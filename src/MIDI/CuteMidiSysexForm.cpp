#include "MIDI.h"

CuteMidiSysex& CuteMidiSysexList::Add() { return items.Add(); }
int CuteMidiSysexList::GetCount() const { return items.GetCount(); }
CuteMidiSysex& CuteMidiSysexList::operator[](int i) { return items[i]; }
CuteMidiSysex::CuteMidiSysex() {}
void CuteMidiSysex::SetName(const String& name) { this->name = name; }
const String& CuteMidiSysex::GetName() const { return name; }
void CuteMidiSysex::SetData(const String& data) { this->data = data; }
const String& CuteMidiSysex::GetData() const { return data; }
CuteMidiSysexForm::CuteMidiSysexForm() { Add(list.VSizePos(0, 32).HSizePos()); Add(ok_button.SetLabel("OK").BottomPos(4, 24).RightPos(80, 64)); Add(cancel_button.SetLabel("Cancel").BottomPos(4, 24).RightPos(8, 64)); SetRect(0,0,420,260); }
void CuteMidiSysexForm::SetSysexList(CuteMidiSysexList* sysex_list) { this->sysex_list = sysex_list; }
CuteMidiSysexList* CuteMidiSysexForm::GetSysexList() const { return sysex_list; }
