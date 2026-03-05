#include "../../Cool.h"
#include "AudioInfo.h"
#include "AudioStreamInfo.h"

AudioInfo::AudioInfo(const std::shared_ptr<Mlt::Producer>& producer)
{
    m_list.Create<AudioStreamInfo>(producer, 0, false);
}

AudioInfo::~AudioInfo() = default;

int AudioInfo::size() const
{
    return m_list.GetCount();
}

AudioStreamInfo const* AudioInfo::info(int pos) const
{
    if (pos < 0 || pos >= m_list.GetCount()) {
        return nullptr;
    }
    return &m_list[pos];
}

void AudioInfo::dumpInfo() const
{
    for (int i = 0; i < m_list.GetCount(); ++i) {
        m_list[i].dumpInfo();
    }
}
