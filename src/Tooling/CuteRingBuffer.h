#ifndef _Tooling_CuteRingBuffer_h_
#define _Tooling_CuteRingBuffer_h_

template <class T>
class CuteRingBuffer {
public:
    CuteRingBuffer(unsigned short channel_count = 0, unsigned int buffer_size = 0)
        : channel_count(channel_count), buffer_size(buffer_size), read_position(0), write_position(0) {
        channels.SetCount(channel_count);
        for (int i = 0; i < channels.GetCount(); ++i)
            channels[i].SetCount((int)buffer_size, T());
    }

    unsigned short GetChannelCount() const { return channel_count; }
    unsigned int GetBufferSize() const { return buffer_size; }
    unsigned int GetReadableCount() const { return write_position >= read_position ? write_position - read_position : 0; }
    unsigned int GetWritableCount() const { return buffer_size > GetReadableCount() ? buffer_size - GetReadableCount() : 0; }
    void Reset() { read_position = 0; write_position = 0; }

private:
    unsigned short channel_count = 0;
    unsigned int buffer_size = 0;
    Vector< Vector<T> > channels;
    unsigned int read_position = 0;
    unsigned int write_position = 0;
};

#endif
