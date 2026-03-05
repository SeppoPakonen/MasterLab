#ifndef _Cool_lib_audio_AudioInfo_h_
#define _Cool_lib_audio_AudioInfo_h_

// Converted from tmp/k/src/lib/audio/audioInfo.h
// Phase-1 conversion: Qt/MLT-heavy implementation replaced with compile-safe U++ placeholders.

namespace std {
template <class T>
class shared_ptr;
}

namespace Mlt {
class Producer;
}

class AudioStreamInfo;

class AudioInfo {
public:
    explicit AudioInfo(const std::shared_ptr<Mlt::Producer>& producer);
    ~AudioInfo();

    int size() const;
    AudioStreamInfo const* info(int pos) const;

    void dumpInfo() const;

private:
    Array<AudioStreamInfo> m_list;
};

#endif
