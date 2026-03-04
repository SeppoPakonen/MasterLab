#include "MIDI.h"

void CuteInstrumentData::SetValue(int key, const String& value) { data.GetAdd(key) = value; }
String CuteInstrumentData::GetValue(int key) const { int index = data.Find(key); return index >= 0 ? data[index] : String(); }
void CuteInstrumentData::Clear() { data.Clear(); }
CuteInstrument::CuteInstrument() {}
void CuteInstrument::SetName(const String& name) { this->name = name; }
const String& CuteInstrument::GetName() const { return name; }
void CuteInstrument::SetBank(int bank) { this->bank = bank; }
int CuteInstrument::GetBank() const { return bank; }
void CuteInstrument::SetProgram(int program) { this->program = program; }
int CuteInstrument::GetProgram() const { return program; }
CuteInstrument& CuteInstrumentList::GetAdd(const String& key) { return items.GetAdd(key); }
const VectorMap<String, CuteInstrument>& CuteInstrumentList::GetItems() const { return items; }
