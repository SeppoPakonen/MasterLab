#ifndef _MIDI_CuteMidiSequence_h_
#define _MIDI_CuteMidiSequence_h_

class CuteMidiSequence {
public:
    CuteMidiSequence();
    ~CuteMidiSequence();
    void AddEvent(CuteMidiEvent* event);
    int GetEventCount() const;
    CuteMidiEvent* GetEvent(int i) const;
    void Clear();
    void SetChannel(unsigned short channel);
    unsigned short GetChannel() const;

private:
    Array<CuteMidiEvent> events;
    unsigned short channel = 0;
};

#endif
