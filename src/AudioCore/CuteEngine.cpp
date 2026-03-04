#include "AudioCore.h"

CuteEngine::CuteEngine() {}
CuteEngine::~CuteEngine() {}
void CuteEngine::SetName(const String& name) { this->name = name; }
const String& CuteEngine::GetName() const { return name; }
void CuteEngine::SetActivated(bool activated) { this->activated = activated; }
bool CuteEngine::IsActivated() const { return activated; }
void CuteEngine::SetRunning(bool running) { this->running = running; }
bool CuteEngine::IsRunning() const { return running; }
void CuteEngine::SetBufferSize(int buffer_size) { this->buffer_size = buffer_size; }
int CuteEngine::GetBufferSize() const { return buffer_size; }
void CuteEngine::SetSampleRate(int sample_rate) { this->sample_rate = sample_rate; }
int CuteEngine::GetSampleRate() const { return sample_rate; }
void CuteEngine::Open() { activated = true; }
void CuteEngine::Close() { activated = false; running = false; }
void CuteEngine::Start() { if(activated) running = true; }
void CuteEngine::Stop() { running = false; }
void CuteEngine::Reset() { running = false; }

CuteBus::CuteBus() {}
CuteBus::~CuteBus() {}
void CuteBus::SetName(const String& name) { this->name = name; }
const String& CuteBus::GetName() const { return name; }
void CuteBus::SetMode(BusMode mode) { this->mode = mode; }
CuteBus::BusMode CuteBus::GetMode() const { return mode; }
void CuteBus::SetMonitor(bool monitor) { this->monitor = monitor; }
bool CuteBus::IsMonitor() const { return monitor; }
void CuteBus::SetGain(double gain) { this->gain = gain; }
double CuteBus::GetGain() const { return gain; }
void CuteBus::SetPanning(double panning) { this->panning = panning; }
double CuteBus::GetPanning() const { return panning; }
