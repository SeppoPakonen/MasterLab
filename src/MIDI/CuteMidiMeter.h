#ifndef _MIDI_CuteMidiMeter_h_
#define _MIDI_CuteMidiMeter_h_

class CuteMidiMonitor;
class CuteAudioMeter;
class CuteAudioOutputMonitor;

class CuteMidiMeterScale : public CuteMeterScale {
public:
    typedef CuteMidiMeterScale CLASSNAME;
    CuteMidiMeterScale(CuteMeter* meter = nullptr);
    void PaintScale(Draw& draw) override;
};

class CuteMidiMeterValue : public CuteMeterValue {
public:
    CuteMidiMeterValue(CuteMeter* meter = nullptr);
    void Refresh(unsigned long stamp) override;
};

class CuteMidiMeterLed : public CuteMeterValue {
public:
    enum { LedOff = 0, LedOn = 1, LedCount = 2 };
    CuteMidiMeterLed(CuteMeter* meter = nullptr);
    void Refresh(unsigned long stamp) override;
private:
    int state = LedOff;
};

class CuteMidiMeter : public CuteMeter {
public:
    enum { Peak = 0, Hold, Led };
    CuteMidiMeter();
};

class CuteMidiComboMeter : public ParentCtrl {
public:
    typedef CuteMidiComboMeter CLASSNAME;
    CuteMidiComboMeter();
private:
    CuteMidiMeter meter;
};

class CuteMidiMixerMeter : public CuteMixerMeter {
public:
    typedef CuteMidiMixerMeter CLASSNAME;
    CuteMidiMixerMeter();
};

#endif
