#ifndef _MIDI_CuteMidiMonitor_h_
#define _MIDI_CuteMidiMonitor_h_

class CuteTimeScale;

class CuteMidiMonitor : public CuteMonitor {
public:
    CuteMidiMonitor();
    void Update() override;
    void ProcessEvent(const CuteMidiEvent& event);
    int GetEventCount() const;
private:
    int event_count = 0;
};

#endif
