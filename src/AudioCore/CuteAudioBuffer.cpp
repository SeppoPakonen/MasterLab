#include "AudioCore.h"

namespace am {
namespace Audio {

// --- CuteAudioBuffer ---
CuteAudioBuffer::CuteAudioBuffer(CuteAudioBufferThread* sync_thread, unsigned short channels)
: sync_thread(sync_thread), channels(channels)
{
	
}

CuteAudioBuffer::~CuteAudioBuffer()
{
	
}

void CuteAudioBuffer::InitSync()
{
	SetSyncFlag(SyncFlag::InitSyncFlag);
}

// ... other CuteAudioBuffer methods ...

} // namespace Audio
} // namespace am
