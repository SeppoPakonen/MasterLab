#include "VSTHost.h"

CutePluginFile::CutePluginFile() {}
CutePluginFile::CutePluginFile(const String& filename) : filename(filename) {}
void CutePluginFile::SetFilename(const String& filename) { this->filename = filename; }
const String& CutePluginFile::GetFilename() const { return filename; }
bool CutePluginFile::Open() { is_open = true; return is_open; }
void CutePluginFile::Close() { is_open = false; }
bool CutePluginFile::IsOpen() const { return is_open; }
void CutePluginFile::SetAutoUnload(bool auto_unload) { this->auto_unload = auto_unload; }
bool CutePluginFile::IsAutoUnload() const { return auto_unload; }
void CutePluginFile::AddRef() { ++ref_count; }
void CutePluginFile::RemoveRef() { if (ref_count > 0) --ref_count; }
int CutePluginFile::GetRefCount() const { return ref_count; }
CutePluginFile& CutePluginFile::AddFile(const String& filename) { static VectorMap<String, CutePluginFile> files; int index = files.Find(filename); if (index < 0) index = files.Add(filename, CutePluginFile(filename)); return files[index]; }
void CutePluginFile::RemoveFile(const String& filename) { static VectorMap<String, CutePluginFile> files; int index = files.Find(filename); if (index >= 0) files.Remove(index); }
void CutePluginFile::ClearFiles() {}

CutePluginType::CutePluginType() {}
void CutePluginType::SetFile(CutePluginFile* file) { this->file = file; }
CutePluginFile* CutePluginType::GetFile() const { return file; }
void CutePluginType::SetIndex(int index) { this->index = index; }
int CutePluginType::GetIndex() const { return index; }
void CutePluginType::SetTypeHint(Hint type_hint) { this->type_hint = type_hint; }
CutePluginType::Hint CutePluginType::GetTypeHint() const { return type_hint; }
void CutePluginType::SetName(const String& name) { this->name = name; }
const String& CutePluginType::GetName() const { return name; }
void CutePluginType::SetLabel(const String& label) { this->label = label; }
const String& CutePluginType::GetLabel() const { return label; }
void CutePluginType::SetUniqueId(uint32 unique_id) { this->unique_id = unique_id; }
uint32 CutePluginType::GetUniqueId() const { return unique_id; }
void CutePluginType::SetPortCounts(int audio_input_count, int audio_output_count, int midi_input_count, int midi_output_count, int control_input_count, int control_output_count) { this->audio_input_count = audio_input_count; this->audio_output_count = audio_output_count; this->midi_input_count = midi_input_count; this->midi_output_count = midi_output_count; this->control_input_count = control_input_count; this->control_output_count = control_output_count; }
int CutePluginType::GetAudioInputCount() const { return audio_input_count; }
int CutePluginType::GetAudioOutputCount() const { return audio_output_count; }
int CutePluginType::GetMidiInputCount() const { return midi_input_count; }
int CutePluginType::GetMidiOutputCount() const { return midi_output_count; }
int CutePluginType::GetControlInputCount() const { return control_input_count; }
int CutePluginType::GetControlOutputCount() const { return control_output_count; }
int CutePluginType::GetInstances() const { return instances; }
String CutePluginType::GetAboutText() const { return Format("%s (%s)", name, GetHintText(type_hint)); }
String CutePluginType::GetHintText(Hint type_hint) { static const char* text[] = {"Any", "Ladspa", "Dssi", "Vst2", "Vst3", "Clap", "Lv2", "Insert", "AuxSend", "Control"}; return text[type_hint >= Any && type_hint <= Control ? type_hint : Any]; }

CutePlugin::Param::Param() {}
void CutePlugin::Param::SetIndex(int index) { this->index = index; }
int CutePlugin::Param::GetIndex() const { return index; }
void CutePlugin::Param::SetName(const String& name) { this->name = name; }
const String& CutePlugin::Param::GetName() const { return name; }
void CutePlugin::Param::SetMinValue(double min_value) { this->min_value = min_value; }
double CutePlugin::Param::GetMinValue() const { return min_value; }
void CutePlugin::Param::SetMaxValue(double max_value) { this->max_value = max_value; }
double CutePlugin::Param::GetMaxValue() const { return max_value; }
void CutePlugin::Param::SetDefaultValue(double default_value) { this->default_value = default_value; }
double CutePlugin::Param::GetDefaultValue() const { return default_value; }
void CutePlugin::Param::SetValue(double value) { previous_value = this->value; this->value = value; }
double CutePlugin::Param::GetValue() const { return value; }
void CutePlugin::Param::SetPreviousValue(double previous_value) { this->previous_value = previous_value; }
double CutePlugin::Param::GetPreviousValue() const { return previous_value; }
void CutePlugin::Param::SetDecimalCount(int decimal_count) { this->decimal_count = decimal_count; }
int CutePlugin::Param::GetDecimalCount() const { return decimal_count; }
void CutePlugin::Param::SetFlags(bool bounded_below, bool bounded_above, bool integer_value, bool toggled, bool display_value) { this->bounded_below = bounded_below; this->bounded_above = bounded_above; this->integer_value = integer_value; this->toggled = toggled; this->display_value = display_value; }
bool CutePlugin::Param::IsBoundedBelow() const { return bounded_below; }
bool CutePlugin::Param::IsBoundedAbove() const { return bounded_above; }
bool CutePlugin::Param::IsInteger() const { return integer_value; }
bool CutePlugin::Param::IsToggled() const { return toggled; }
bool CutePlugin::Param::IsDisplay() const { return display_value; }
String CutePlugin::Param::GetDisplayText() const { return Format("%.*f", decimal_count, value); }
void CutePlugin::Param::Reset() { value = default_value; previous_value = default_value; }

CutePlugin::Property::Property() {}
void CutePlugin::Property::SetKey(const String& key) { this->key = key; }
const String& CutePlugin::Property::GetKey() const { return key; }
void CutePlugin::Property::SetKeyIndex(int key_index) { this->key_index = key_index; }
int CutePlugin::Property::GetKeyIndex() const { return key_index; }
void CutePlugin::Property::SetValue(const Value& value) { this->value = value; }
const Value& CutePlugin::Property::GetValue() const { return value; }
void CutePlugin::Property::SetString(bool string_value) { this->string_value = string_value; }
bool CutePlugin::Property::IsString() const { return string_value; }
void CutePlugin::Property::SetPath(bool path_value) { this->path_value = path_value; }
bool CutePlugin::Property::IsPath() const { return path_value; }
void CutePlugin::Property::SetAutomatable(bool automatable) { this->automatable = automatable; }
bool CutePlugin::Property::IsAutomatable() const { return automatable; }

CutePlugin::CutePlugin() {}
CutePlugin::~CutePlugin() {}
void CutePlugin::SetList(CutePluginList* list) { this->list = list; }
CutePluginList* CutePlugin::GetList() const { return list; }
void CutePlugin::SetType(CutePluginType* type) { this->type = type; }
CutePluginType* CutePlugin::GetType() const { return type; }
void CutePlugin::SetUniqueId(uint32 unique_id) { this->unique_id = unique_id; }
uint32 CutePlugin::GetUniqueId() const { return unique_id; }
void CutePlugin::SetLabel(const String& label) { this->label = label; }
const String& CutePlugin::GetLabel() const { return label; }
void CutePlugin::SetAlias(const String& alias) { this->alias = alias; }
const String& CutePlugin::GetAlias() const { return alias; }
void CutePlugin::SetActivated(bool activated) { this->activated = activated; }
bool CutePlugin::IsActivated() const { return activated; }
void CutePlugin::SetChannelCount(int channel_count) { this->channel_count = channel_count; }
int CutePlugin::GetChannelCount() const { return channel_count; }
void CutePlugin::AddParam(const Param& param) { params.Add(param); }
Vector<CutePlugin::Param>& CutePlugin::GetParams() { return params; }
const Vector<CutePlugin::Param>& CutePlugin::GetParams() const { return params; }
void CutePlugin::AddProperty(const Property& property) { properties.Add(property); }
Vector<CutePlugin::Property>& CutePlugin::GetProperties() { return properties; }
const Vector<CutePlugin::Property>& CutePlugin::GetProperties() const { return properties; }
void CutePlugin::SetProgramList(const Vector<Program>& program_list) { this->program_list = program_list; }
const Vector<CutePlugin::Program>& CutePlugin::GetProgramList() const { return program_list; }
void CutePlugin::SetNoteNameList(const Vector<NoteName>& note_name_list) { this->note_name_list = note_name_list; }
const Vector<CutePlugin::NoteName>& CutePlugin::GetNoteNameList() const { return note_name_list; }
void CutePlugin::SetDirectAccessParamIndex(int direct_access_param_index) { this->direct_access_param_index = direct_access_param_index; }
int CutePlugin::GetDirectAccessParamIndex() const { return direct_access_param_index; }
void CutePlugin::Reset() { activated = false; editor_visible = false; form_visible = false; for (int i = 0; i < params.GetCount(); ++i) params[i].Reset(); }
bool CutePlugin::Activate() { activated = true; return true; }
void CutePlugin::Deactivate() { activated = false; }
void CutePlugin::Process() {}
bool CutePlugin::OpenEditor() { editor_visible = true; return true; }
void CutePlugin::CloseEditor() { editor_visible = false; }
bool CutePlugin::IsEditorVisible() const { return editor_visible; }
bool CutePlugin::OpenForm() { form_visible = true; return true; }
void CutePlugin::CloseForm() { form_visible = false; }
bool CutePlugin::IsFormVisible() const { return form_visible; }
void CutePlugin::UpdateListViews() {}

CutePluginList::MidiProgramSubject::MidiProgramSubject() {}
CutePluginList::MidiProgramSubject::MidiProgramSubject(int bank, int program) : bank(bank), program(program) {}
void CutePluginList::MidiProgramSubject::SetProgram(int bank, int program) { this->bank = bank; this->program = program; }
int CutePluginList::MidiProgramSubject::GetBank() const { return bank; }
int CutePluginList::MidiProgramSubject::GetProgram() const { return program; }

CutePluginList::CutePluginList() {}
void CutePluginList::SetName(const String& name) { this->name = name; }
const String& CutePluginList::GetName() const { return name; }
void CutePluginList::SetFlags(int flags) { this->flags = flags; }
int CutePluginList::GetFlags() const { return flags; }
bool CutePluginList::IsMidi() const { return (flags & Midi) != 0; }
bool CutePluginList::IsMidiBus() const { return (flags & MidiBus) == MidiBus; }
void CutePluginList::SetChannelCount(int channel_count) { this->channel_count = channel_count; }
int CutePluginList::GetChannelCount() const { return channel_count; }
void CutePluginList::AddPlugin(CutePlugin& plugin) { plugin.SetList(this); plugin_list.Add().Pick(pick(plugin)); }
void CutePluginList::InsertPlugin(int index, CutePlugin& plugin) { plugin.SetList(this); if (index < 0 || index > plugin_list.GetCount()) index = plugin_list.GetCount(); plugin_list.Insert(index).Pick(pick(plugin)); }
void CutePluginList::MovePlugin(int from, int to) { if (from < 0 || from >= plugin_list.GetCount() || to < 0 || to >= plugin_list.GetCount() || from == to) return; CutePlugin plugin = pick(plugin_list[from]); plugin_list.Remove(from); plugin_list.Insert(to).Pick(pick(plugin)); }
void CutePluginList::RemovePlugin(int index) { if (index >= 0 && index < plugin_list.GetCount()) plugin_list.Remove(index); }
int CutePluginList::GetPluginCount() const { return plugin_list.GetCount(); }
CutePlugin* CutePluginList::GetPlugin(int index) { return index >= 0 && index < plugin_list.GetCount() ? &plugin_list[index] : nullptr; }
const CutePlugin* CutePluginList::GetPlugin(int index) const { return index >= 0 && index < plugin_list.GetCount() ? &plugin_list[index] : nullptr; }
void CutePluginList::AddView(CutePluginListView* view) { views.Add(view); }
void CutePluginList::RemoveView(CutePluginListView* view) { views.RemoveKey(view); }
void CutePluginList::SetMidiBank(int midi_bank) { this->midi_bank = midi_bank; midi_program_subject.SetProgram(midi_bank, midi_program); }
int CutePluginList::GetMidiBank() const { return midi_bank; }
void CutePluginList::SetMidiProgram(int midi_program) { this->midi_program = midi_program; midi_program_subject.SetProgram(midi_bank, midi_program); }
int CutePluginList::GetMidiProgram() const { return midi_program; }
void CutePluginList::SetAudioOutputBusName(const String& audio_output_bus_name) { this->audio_output_bus_name = audio_output_bus_name; }
const String& CutePluginList::GetAudioOutputBusName() const { return audio_output_bus_name; }
CutePluginList::MidiProgramSubject& CutePluginList::GetMidiProgramSubject() { return midi_program_subject; }
uint32 CutePluginList::CreateUniqueId() const { return plugin_list.GetCount() ? 1000 + plugin_list.GetCount() : 1000; }
