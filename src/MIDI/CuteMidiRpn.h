#ifndef _MIDI_CuteMidiRpn_h_
#define _MIDI_CuteMidiRpn_h_

class CuteMidiRpn {
public:
    enum Type { None = 0, CC = 0x10, Rpn = 0x20, Nrpn = 0x30, Cc14 = 0x40 };

    struct Event {
        unsigned long time = 0;
        int port = 0;
        unsigned char status = 0;
        unsigned short param = 0;
        unsigned short value = 0;
    };

    CuteMidiRpn();
    bool Process(const Event& event);
    bool Dequeue(Event& event);
    bool IsPending() const;
    void Clear();

private:
    Vector<Event> pending;
};

#endif
