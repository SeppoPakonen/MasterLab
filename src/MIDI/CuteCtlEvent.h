#ifndef _MIDI_CuteCtlEvent_h_
#define _MIDI_CuteCtlEvent_h_

struct CuteCtlEvent {
    enum EventType {
        Controller = 0,
        NoteOn,
        NoteOff,
    };

    CuteCtlEvent(EventType type = Controller, unsigned short channel = 0, unsigned short param = 0, unsigned short value = 0)
        : type(type), channel(channel), param(param), value(value) {}

    EventType type;
    unsigned short channel;
    unsigned short param;
    unsigned short value;
};

#endif
