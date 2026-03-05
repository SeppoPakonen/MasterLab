#include "AudioCore.h"

void CuteAudioEngineProxy::NotifyShutEvent() {}
void CuteAudioEngineProxy::NotifyXrunEvent() {}
void CuteAudioEngineProxy::NotifyPortEvent() {}
void CuteAudioEngineProxy::NotifyBuffEvent(unsigned int buffer_size) {
	(void)buffer_size;
}
void CuteAudioEngineProxy::NotifySessEvent(void* session_arg) {
	(void)session_arg;
}
void CuteAudioEngineProxy::NotifySyncEvent(unsigned long play_head, bool is_playing) {
	(void)play_head;
	(void)is_playing;
}
void CuteAudioEngineProxy::NotifyPropEvent() {}
void CuteAudioEngineProxy::NotifySelfEvent() {}

CuteAudioEngine::CuteAudioEngine() {}

bool CuteAudioEngine::Init() {
	return true;
}

const CuteAudioEngineProxy* CuteAudioEngine::GetProxy() const {
	return &proxy;
}

int CuteAudioEngine::Process(unsigned int frame_count) {
	(void)frame_count;
	return 0;
}

void CuteAudioEngine::Timebase(unsigned long play_head, int is_new_pos) {
	(void)play_head;
	(void)is_new_pos;
}

bool CuteAudioEngine::LoadElement(CuteDocument* document, CuteXmlElement* element) {
	(void)document;
	(void)element;
	return true;
}

bool CuteAudioEngine::SaveElement(CuteDocument* document, CuteXmlElement* element) const {
	(void)document;
	(void)element;
	return true;
}

void CuteAudioEngine::SetSessionId(const String& session_id) {
	this->session_id = session_id;
}

const String& CuteAudioEngine::GetSessionId() const {
	return session_id;
}

unsigned int CuteAudioEngine::GetSampleRate() const {
	return sample_rate;
}

unsigned int CuteAudioEngine::GetBufferSize() const {
	return buffer_size;
}

unsigned int CuteAudioEngine::GetBufferSizeEx() const {
	return buffer_size + buffer_offset;
}

unsigned int CuteAudioEngine::GetBufferOffset() const {
	return buffer_offset;
}

unsigned int CuteAudioEngine::GetBlockSize() const {
	return block_size;
}

void CuteAudioEngine::SetMasterAutoConnect(bool master_auto_connect) {
	this->master_auto_connect = master_auto_connect;
}

bool CuteAudioEngine::IsMasterAutoConnect() const {
	return master_auto_connect;
}

void CuteAudioEngine::SetFreewheel(bool freewheel) {
	this->freewheel = freewheel;
}

bool CuteAudioEngine::IsFreewheel() const {
	return freewheel;
}

void CuteAudioEngine::SetExporting(bool exporting) {
	this->exporting = exporting;
}

bool CuteAudioEngine::IsExporting() const {
	return exporting;
}

unsigned long CuteAudioEngine::GetExportStart() const {
	return export_start;
}

unsigned long CuteAudioEngine::GetExportOffset() const {
	return export_offset;
}

unsigned long CuteAudioEngine::GetExportLength() const {
	return export_length;
}

bool CuteAudioEngine::FileExport(const String& export_path, unsigned long export_start, unsigned long export_end, int export_format) {
	(void)export_path;
	(void)export_format;
	this->export_start = export_start;
	export_offset = export_start;
	export_length = export_end >= export_start ? export_end - export_start : 0;
	return true;
}

void CuteAudioEngine::TrackMute(CuteTrack* track, bool mute) {
	(void)track;
	(void)mute;
}

void CuteAudioEngine::SetMetronome(bool metronome) {
	this->metronome = metronome;
}

bool CuteAudioEngine::IsMetronome() const {
	return metronome;
}

void CuteAudioEngine::SetMetroEnabled(bool metro_enabled) {
	this->metro_enabled = metro_enabled;
}

bool CuteAudioEngine::IsMetroEnabled() const {
	return metro_enabled;
}

void CuteAudioEngine::SetMetroBus(bool metro_bus) {
	this->metro_bus = metro_bus;
}

bool CuteAudioEngine::IsMetroBus() const {
	return metro_bus;
}

void CuteAudioEngine::ResetMetroBus() {
	metro_bus = false;
}

void CuteAudioEngine::SetMetroAutoConnect(bool metro_auto_connect) {
	this->metro_auto_connect = metro_auto_connect;
}

bool CuteAudioEngine::IsMetroAutoConnect() const {
	return metro_auto_connect;
}

void CuteAudioEngine::SetMetroBarFileName(const String& file_name) {
	metro_bar_file_name = file_name;
}

const String& CuteAudioEngine::GetMetroBarFileName() const {
	return metro_bar_file_name;
}

void CuteAudioEngine::SetMetroBarGain(float gain) {
	metro_bar_gain = gain;
}

float CuteAudioEngine::GetMetroBarGain() const {
	return metro_bar_gain;
}

void CuteAudioEngine::SetMetroBeatFileName(const String& file_name) {
	metro_beat_file_name = file_name;
}

const String& CuteAudioEngine::GetMetroBeatFileName() const {
	return metro_beat_file_name;
}

void CuteAudioEngine::SetMetroBeatGain(float gain) {
	metro_beat_gain = gain;
}

float CuteAudioEngine::GetMetroBeatGain() const {
	return metro_beat_gain;
}

void CuteAudioEngine::SetMetroOffset(unsigned long metro_offset) {
	this->metro_offset = metro_offset;
}

unsigned long CuteAudioEngine::GetMetroOffset() const {
	return metro_offset;
}

void CuteAudioEngine::ResetMetro(bool count_in) {
	(void)count_in;
}

void CuteAudioEngine::SetCountIn(bool count_in) {
	this->count_in = count_in;
}

bool CuteAudioEngine::IsCountIn() const {
	return count_in;
}

void CuteAudioEngine::SetCountInMode(CountInMode count_in_mode) {
	this->count_in_mode = count_in_mode;
}

CuteAudioEngine::CountInMode CuteAudioEngine::GetCountInMode() const {
	return count_in_mode;
}
