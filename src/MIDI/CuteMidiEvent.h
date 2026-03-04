#ifndef _MIDI_CuteMidiEvent_h_
#define _MIDI_CuteMidiEvent_h_

class CuteMidiEvent : public CuteList<CuteMidiEvent>::Link {
public:
    enum EventType {
        NoteOff = 0x80,
        NoteOn = 0x90,
        KeyPress = 0xa0,
        Controller = 0xb0,
        ProgramChange = 0xc0,
        ChannelPressure = 0xd0,
        PitchBend = 0xe0,
        Sysex = 0xf0,
        Meta = 0xff,
        RegParam = 0x10,
        NonRegParam = 0x20,
        Control14 = 0x30
    };

    enum MetaType {
        Sequence = 0x00,
        Text = 0x01,
        Copyright = 0x02,
        TrackName = 0x03,
        Instrument = 0x04,
        Lyric = 0x05,
        Marker = 0x06,
        Cue = 0x07,
        Channel = 0x20,
        Port = 0x21,
        EndOfTrack = 0x2f,
        Tempo = 0x51,
        Smpte = 0x54,
        TimeSignature = 0x58,
        KeySignature = 0x59,
        Proprietary = 0x7f
    };

    CuteMidiEvent(unsigned long time = 0, EventType type = NoteOn, unsigned short param = 0, unsigned short value = 0, unsigned long duration = 0);
    CuteMidiEvent(const CuteMidiEvent& e);
    ~CuteMidiEvent();

    unsigned long GetTime() const;
    EventType GetType() const;
    unsigned char GetNote() const;
    unsigned char GetVelocity() const;
    unsigned short GetParam() const;
    unsigned short GetValue() const;
    unsigned long GetDuration() const;

    void SetTime(unsigned long time);
    void SetType(EventType type);
    void AdjustTime(unsigned long offset);
    void SetNote(unsigned char note);
    void SetVelocity(unsigned char velocity);
    void SetParam(unsigned short param);
    void SetValue(unsigned short value);
    void SetDuration(unsigned long duration);
    int GetPitchBend() const;
    void SetPitchBend(int pitch_bend);

private:
    unsigned long time = 0;
    EventType type = NoteOn;
    unsigned short param = 0;
    unsigned short value = 0;
    unsigned long duration = 0;
};

inline CuteMidiEvent::CuteMidiEvent(unsigned long time, EventType type, unsigned short param, unsigned short value, unsigned long duration)
    : time(time), type(type), param(param), value(value), duration(duration) {}

inline CuteMidiEvent::CuteMidiEvent(const CuteMidiEvent& e)
    : time(e.time), type(e.type), param(e.param), value(e.value), duration(e.duration) {}

inline CuteMidiEvent::~CuteMidiEvent() {}
inline unsigned long CuteMidiEvent::GetTime() const { return time; }
inline CuteMidiEvent::EventType CuteMidiEvent::GetType() const { return type; }
inline unsigned char CuteMidiEvent::GetNote() const { return (unsigned char)param; }
inline unsigned char CuteMidiEvent::GetVelocity() const { return (unsigned char)value; }
inline unsigned short CuteMidiEvent::GetParam() const { return param; }
inline unsigned short CuteMidiEvent::GetValue() const { return value; }
inline unsigned long CuteMidiEvent::GetDuration() const { return duration; }
inline void CuteMidiEvent::SetTime(unsigned long time) { this->time = time; }
inline void CuteMidiEvent::SetType(EventType type) { this->type = type; }
inline void CuteMidiEvent::AdjustTime(unsigned long offset) { time = time > offset ? time - offset : 0; }
inline void CuteMidiEvent::SetNote(unsigned char note) { param = note; }
inline void CuteMidiEvent::SetVelocity(unsigned char velocity) { value = velocity; }
inline void CuteMidiEvent::SetParam(unsigned short param) { this->param = param; }
inline void CuteMidiEvent::SetValue(unsigned short value) { this->value = value; }
inline void CuteMidiEvent::SetDuration(unsigned long duration) { this->duration = duration; }
inline int CuteMidiEvent::GetPitchBend() const { return int(value) - 0x2000; }
inline void CuteMidiEvent::SetPitchBend(int pitch_bend) { value = (unsigned short)(0x2000 + pitch_bend); }

#endif
