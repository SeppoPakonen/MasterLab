#include "AudioCore.h"

namespace am {
namespace Audio {

// --- CuteAudioEngineProxy ---
CuteAudioEngineProxy::CuteAudioEngineProxy() {}
CuteAudioEngineProxy::~CuteAudioEngineProxy() {}
void CuteAudioEngineProxy::Start() {}
void CuteAudioEngineProxy::Stop() {}
bool CuteAudioEngineProxy::IsRunning() const { return false; }
int CuteAudioEngineProxy::GetSampleRate() const { return 0; }
void CuteAudioEngineProxy::SetMasterVolume(float) {}

// --- CuteAudioEngine ---
CuteAudioEngine::CuteAudioEngine() {}
CuteAudioEngine::~CuteAudioEngine() {}
void CuteAudioEngine::Init(int, int, int, void*) {}
void CuteAudioEngine::Start() {}
void CuteAudioEngine::Stop() {}
bool CuteAudioEngine::IsRunning() const { return false; }
int CuteAudioEngine::GetSampleRate() const { return 0; }
void CuteAudioEngine::SetMasterVolume(float) {}

} // namespace Audio
} // namespace am
