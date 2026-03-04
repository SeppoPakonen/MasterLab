#ifndef _MIDI_CuteMidiTimer_h_
#define _MIDI_CuteMidiTimer_h_

class CuteMidiTimer {
public:
    CuteMidiTimer();
    void Start();
    void Stop();
    bool IsRunning() const;
private:
    bool running = false;
};

#endif
