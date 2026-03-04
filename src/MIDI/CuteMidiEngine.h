#ifndef _MIDI_CuteMidiEngine_h_
#define _MIDI_CuteMidiEngine_h_

class CuteMidiBus;
class CuteMidiClip;
class CuteMidiSequence;
class CuteMidiMonitor;
class CuteMidiPlayer;
class CutePluginList;
class CuteCurveList;

class CuteMidiEngineProxy {
public:
    void NotifyMmcEvent(const CuteCtlEvent& mmc_event);
    void NotifyCtlEvent(const CuteCtlEvent& ctl_event);
    void NotifySppEvent(int spp_cmd, unsigned short song_pos);
    void NotifyClkEvent(float tempo);
    void NotifyInpEvent(unsigned short flags);
};

class CuteMidiEngine : public CuteEngine {
public:
    enum CountInMode { CountInNone = 0, CountInPlayback, CountInRecording };
    enum InpFlag { InpNone = 0, InpReset = 1, InpEvent = 2 };

    struct InpEvent {
        CuteMidiClip* clip = nullptr;
        CuteMidiEvent* event = nullptr;
    };

    class CuteMidiBus : public CuteBus {
    public:
        struct NoteOff {
            unsigned short note = 0;
            unsigned long time = 0;
        };
    };

    CuteMidiEngine();
    bool Init();
    CuteMidiEngineProxy* GetProxy();
    void Process();
    void Sync();
    void ResetTime();
    void ResetSync();
    void ResetTempo();
    void ResetAllMonitors();
    void ResetAllControllers(bool force_immediate);
    bool IsResetAllControllersPending() const;
    void ShutOffAllBuses(bool close = false);
    void ShutOffAllTracks();
    void SetReadAhead(unsigned int read_ahead);
    unsigned int GetReadAhead() const;

private:
    CuteMidiEngineProxy proxy;
    unsigned int read_ahead = 0;
    bool reset_all_controllers_pending = false;
};

#endif
