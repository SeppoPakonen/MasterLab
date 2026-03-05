#ifndef _TransportUI_CuteMeter_h_
#define _TransportUI_CuteMeter_h_

class CuteMonitor;
class CuteSubject;
class CuteMidiControlObserver;

class CuteMeter;

class CuteMeterScale : public StaticRect {
public:
    typedef CuteMeterScale CLASSNAME;

    CuteMeterScale(CuteMeter* meter = nullptr);
    CuteMeter* GetMeter() const;
    virtual void PaintScale(Draw& draw);

protected:
    void Paint(Draw& draw) override;
    void DrawLineLabel(Draw& draw, int y, const String& label);

private:
    CuteMeter* meter = nullptr;
    int last_y = 0;
};

class CuteMeterValue : public Ctrl {
public:
    typedef CuteMeterValue CLASSNAME;

    CuteMeterValue(CuteMeter* meter = nullptr);
    virtual ~CuteMeterValue();

    CuteMeter* GetMeter() const;
    virtual void Refresh(unsigned long stamp);

    static void RefreshAll();
    static void UpdateAll();

private:
    CuteMeter* meter = nullptr;
    static Vector<CuteMeterValue*> values;
    static unsigned long stamp;
};

class CuteMeter : public ParentCtrl {
public:
    typedef CuteMeter CLASSNAME;

    CuteMeter();
    virtual ~CuteMeter();

    virtual void SetMonitor(CuteMonitor* monitor);
    virtual CuteMonitor* GetMonitor() const;
    virtual void Reset();

    int Scale(float value) const;
    void SetPeakFalloff(int peak_falloff);
    int GetPeakFalloff() const;
    void SetScaleFactor(float scale_factor);

protected:
    ParentCtrl box;
    CuteMonitor* monitor = nullptr;
    float scale_factor = 0.0f;
    int peak_falloff = 0;
};

class CuteMixerMeter : public ParentCtrl {
public:
    typedef CuteMixerMeter CLASSNAME;

    CuteMixerMeter();
    void SetTitle(const String& title);
    const String& GetTitle() const;

private:
    String title;
    Label title_label;
    CuteMeter meter;
};

#endif
