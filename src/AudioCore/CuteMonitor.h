#ifndef _AudioCore_CuteMonitor_h_
#define _AudioCore_CuteMonitor_h_

class CuteMonitor {
public:
    class Observer : public CuteMidiControlObserver {
    public:
        Observer(CuteMonitor* monitor = nullptr, CuteSubject* subject = nullptr);
        void TriggerUpdate(bool update);
    private:
        CuteMonitor* monitor = nullptr;
    };

    class GainObserver : public Observer {
    public:
        GainObserver(CuteMonitor* monitor = nullptr, CuteSubject* subject = nullptr);
    };

    class PanningObserver : public Observer {
    public:
        PanningObserver(CuteMonitor* monitor = nullptr, CuteSubject* subject = nullptr);
    };

    CuteMonitor(float gain = 1.0f, float panning = 0.0f);
    virtual ~CuteMonitor();

    CuteSubject* GainSubject();
    CuteMidiControlObserver* GainObserverPtr();
    void SetGain(float gain);
    float GetGain() const;
    float GetPrevGain() const;

    CuteSubject* PanningSubject();
    CuteMidiControlObserver* PanningObserverPtr();
    void SetPanning(float panning);
    float GetPanning() const;
    float GetPrevPanning() const;

    virtual void Update() = 0;

protected:
    CuteSubject gain_subject;
    CuteSubject panning_subject;
    GainObserver gain_observer;
    PanningObserver panning_observer;
};

#endif
