#ifndef _Cool_lib_audio_AudioStreamInfo_h_
#define _Cool_lib_audio_AudioStreamInfo_h_

// Converted from tmp/k/src/lib/audio/audioStreamInfo.h
// Phase-1 conversion: Qt/MLT-heavy implementation replaced with compile-safe U++ placeholders.

namespace std {
template <class T>
class shared_ptr;
}

namespace Mlt {
class Producer;
class Properties;
}

using QString = String;
template <class K, class V>
using QMap = VectorMap<K, V>;
template <class T>
using QList = Vector<T>;

class AudioStreamInfo {
public:
    AudioStreamInfo(const std::shared_ptr<Mlt::Producer>& producer, int audio_stream_index, bool playlist = false);
    ~AudioStreamInfo();

    int samplingRate() const;
    int channels(int stream = -1) const;
    QMap<int, QString> streams() const;
    QMap<int, int> streamChannels() const;
    int channelsForStream(int stream) const;
    QList<int> activeStreamChannels() const;
    QMap<int, QString> activeStreams() const;
    int bitrate() const;
    const QString& samplingFormat() const;
    int audio_index() const;
    int ffmpeg_audio_index() const;
    void dumpInfo() const;
    void setAudioIndex(const std::shared_ptr<Mlt::Producer>& producer, int ix);
    QMap<int, QString> streamInfo(const Mlt::Properties& source_properties);
    void updateActiveStreams(const QString& active_streams);
    void renameStream(int ix, const QString& stream_name);

private:
    int m_audio_stream_index{-1};
    QMap<int, QString> m_audio_streams;
    QMap<int, int> m_audio_channels;
    QList<int> m_active_streams;
    int m_ffmpeg_audio_index{0};
    int m_sampling_rate{48000};
    int m_channels{2};
    int m_bit_rate{0};
    QString m_sampling_format{"s16"};
};

#endif
