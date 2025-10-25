#include "AudioBuffer.h"
namespace am {
void AudioBuffer::Resize(int ch, int frames) {
    channels = ch;
    data.SetCount(ch);
    for(int i = 0; i < ch; i++) {
        data[i].SetCount(frames);
    }
}

int AudioBuffer::GetFrames() const {
    if(data.GetCount() > 0) {
        return data[0].GetCount();
    }
    return 0;
}
}