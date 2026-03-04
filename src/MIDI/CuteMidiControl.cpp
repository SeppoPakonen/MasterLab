#include "MIDI.h"

bool CuteMidiControl::MapKey::operator==(const MapKey& other) const { return control_type == other.control_type && channel == other.channel && param == other.param; }
unsigned CuteMidiControl::MapKey::GetHashValue() const { return CombineHash((int)control_type, (int)channel, (int)param); }
void CuteMidiControl::Controller::SetName(const String& name) { this->name = name; }
const String& CuteMidiControl::Controller::GetName() const { return name; }
void CuteMidiControl::Controller::SetFlags(int flags) { this->flags = flags; }
int CuteMidiControl::Controller::GetFlags() const { return flags; }
CuteMidiControl::CuteMidiControl() {}
void CuteMidiControl::MapControl(const MapKey& key, const MapVal& value) { control_map.GetAdd(key) = value; }
bool CuteMidiControl::UnmapControl(const MapKey& key) { int i = control_map.Find(key); if(i >= 0) { control_map.Remove(i); return true; } return false; }
const VectorMap<CuteMidiControl::MapKey, CuteMidiControl::MapVal>& CuteMidiControl::GetControlMap() const { return control_map; }
void CuteMidiControl::AddObserver(CuteMidiControlObserver* observer) { if(observers.Find(observer) < 0) observers.Add(observer); }
void CuteMidiControl::RemoveObserver(CuteMidiControlObserver* observer) { int i = observers.Find(observer); if(i >= 0) observers.Remove(i); }
const Vector<CuteMidiControlObserver*>& CuteMidiControl::GetObservers() const { return observers; }
