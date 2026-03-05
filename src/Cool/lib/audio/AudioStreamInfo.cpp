#include "../../Cool.h"
#include "AudioStreamInfo.h"

AudioStreamInfo::AudioStreamInfo(const std::shared_ptr<Mlt::Producer>& producer, int audio_stream_index, bool playlist)
    : m_audio_stream_index(audio_stream_index)
{
    (void)producer;
    (void)playlist;

    m_audio_streams.Add(0, "Audio");
    m_audio_channels.Add(0, 2);
    m_active_streams.Add(0);
}

AudioStreamInfo::~AudioStreamInfo() = default;

int AudioStreamInfo::samplingRate() const
{
    return m_sampling_rate;
}

int AudioStreamInfo::channels(int stream) const
{
    return channelsForStream(stream);
}

QMap<int, QString> AudioStreamInfo::streams() const
{
    QMap<int, QString> out;
    for (int i = 0; i < m_audio_streams.GetCount(); ++i) {
        out.Add(m_audio_streams.GetKey(i), m_audio_streams[i]);
    }
    return out;
}

QMap<int, int> AudioStreamInfo::streamChannels() const
{
    QMap<int, int> out;
    for (int i = 0; i < m_audio_channels.GetCount(); ++i) {
        out.Add(m_audio_channels.GetKey(i), m_audio_channels[i]);
    }
    return out;
}

int AudioStreamInfo::channelsForStream(int stream) const
{
    int idx = m_audio_channels.Find(stream);
    if (idx >= 0) {
        return m_audio_channels[idx];
    }
    return m_channels;
}

QList<int> AudioStreamInfo::activeStreamChannels() const
{
    QList<int> out;
    for (int i = 0; i < m_active_streams.GetCount(); ++i) {
        out.Add(channelsForStream(m_active_streams[i]));
    }
    return out;
}

QMap<int, QString> AudioStreamInfo::activeStreams() const
{
    QMap<int, QString> out;
    for (int i = 0; i < m_active_streams.GetCount(); ++i) {
        int key = m_active_streams[i];
        int pos = m_audio_streams.Find(key);
        if (pos >= 0) {
            out.Add(key, m_audio_streams[pos]);
        }
    }
    return out;
}

int AudioStreamInfo::bitrate() const
{
    return m_bit_rate;
}

const QString& AudioStreamInfo::samplingFormat() const
{
    return m_sampling_format;
}

int AudioStreamInfo::audio_index() const
{
    return m_audio_stream_index;
}

int AudioStreamInfo::ffmpeg_audio_index() const
{
    return m_ffmpeg_audio_index;
}

void AudioStreamInfo::dumpInfo() const
{
    RLOG("AudioStreamInfo: index=" << m_audio_stream_index << ", channels=" << m_channels << ", rate=" << m_sampling_rate);
}

void AudioStreamInfo::setAudioIndex(const std::shared_ptr<Mlt::Producer>& producer, int ix)
{
    (void)producer;
    m_audio_stream_index = ix;
    m_ffmpeg_audio_index = max(0, ix);
}

QMap<int, QString> AudioStreamInfo::streamInfo(const Mlt::Properties& source_properties)
{
    (void)source_properties;
    return streams();
}

void AudioStreamInfo::updateActiveStreams(const QString& active_streams)
{
    m_active_streams.Clear();
    if (active_streams.IsEmpty()) {
        m_active_streams.Add(0);
        return;
    }

    Vector<String> parts = Split(active_streams, ';');
    for (int i = 0; i < parts.GetCount(); ++i) {
        String p = TrimBoth(parts[i]);
        if (!p.IsEmpty()) {
            m_active_streams.Add(ScanInt(p));
        }
    }
    if (m_active_streams.IsEmpty()) {
        m_active_streams.Add(0);
    }
}

void AudioStreamInfo::renameStream(int ix, const QString& stream_name)
{
    int pos = m_audio_streams.Find(ix);
    if (pos >= 0) {
        m_audio_streams[pos] = stream_name;
    }
}
