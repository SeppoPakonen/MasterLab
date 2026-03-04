#ifndef _MIDI_CuteMidiBuffer_h_
#define _MIDI_CuteMidiBuffer_h_

class CuteMidiBuffer {
public:
    enum { MinBufferSize = 0x400 };

    struct Event {
        unsigned long tick = 0;
        int type = 0;
        int a = 0;
        int b = 0;
    };

    CuteMidiBuffer(unsigned int buffer_size = MinBufferSize);

    unsigned int GetBufferSize() const;
    void Clear();
    bool IsEmpty() const;
    Event* Peek();
    Event* Next();
    Event* Pop();
    bool Push(const Event& event, unsigned long tick = 0);
    bool Insert(const Event& event, unsigned long tick = 0);
    unsigned int GetCount() const;
    Event* At(unsigned int index);
    void Reset(unsigned long tick = 0);

private:
    Vector<Event> buffer;
    unsigned int buffer_size = 0;
    unsigned int buffer_mask = 0;
    unsigned int write_index = 0;
    unsigned int read_index = 0;
};

inline CuteMidiBuffer::CuteMidiBuffer(unsigned int buffer_size) {
    this->buffer_size = MinBufferSize;
    while(this->buffer_size < buffer_size)
        this->buffer_size <<= 1;
    buffer_mask = this->buffer_size - 1;
    buffer.SetCount(this->buffer_size);
}

inline unsigned int CuteMidiBuffer::GetBufferSize() const { return buffer_size; }
inline void CuteMidiBuffer::Clear() { read_index = write_index = 0; }
inline bool CuteMidiBuffer::IsEmpty() const { return read_index == write_index; }
inline CuteMidiBuffer::Event* CuteMidiBuffer::Peek() { return IsEmpty() ? nullptr : &buffer[read_index]; }
inline CuteMidiBuffer::Event* CuteMidiBuffer::Next() { if(!IsEmpty()) read_index = (read_index + 1) & buffer_mask; return Peek(); }
inline CuteMidiBuffer::Event* CuteMidiBuffer::Pop() { unsigned int i = read_index; if(i == write_index) return nullptr; read_index = (i + 1) & buffer_mask; return &buffer[i]; }
inline bool CuteMidiBuffer::Push(const Event& event, unsigned long tick) {
    unsigned int i = (write_index + 1) & buffer_mask;
    if(i == read_index)
        return false;
    buffer[i] = event;
    buffer[i].tick = tick;
    write_index = i;
    return true;
}
inline bool CuteMidiBuffer::Insert(const Event& event, unsigned long tick) { return Push(event, tick); }
inline unsigned int CuteMidiBuffer::GetCount() const { return write_index >= read_index ? write_index - read_index : (write_index - read_index + buffer_size) & buffer_mask; }
inline CuteMidiBuffer::Event* CuteMidiBuffer::At(unsigned int index) { return &buffer[(read_index + index) & buffer_mask]; }
inline void CuteMidiBuffer::Reset(unsigned long tick) { for(unsigned int i = read_index; i != write_index; i = (i + 1) & buffer_mask) buffer[i].tick = tick; }

#endif
