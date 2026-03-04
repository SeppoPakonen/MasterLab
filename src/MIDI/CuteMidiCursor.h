#ifndef _MIDI_CuteMidiCursor_h_
#define _MIDI_CuteMidiCursor_h_

class CuteMidiSequence;

class CuteMidiCursor {
public:
    CuteMidiCursor(CuteMidiSequence* sequence = nullptr);
    void SetSequence(CuteMidiSequence* sequence);
    CuteMidiSequence* GetSequence() const;
    void Reset();
    int Seek(unsigned long time);

private:
    CuteMidiSequence* sequence = nullptr;
    int index = -1;
};

#endif
