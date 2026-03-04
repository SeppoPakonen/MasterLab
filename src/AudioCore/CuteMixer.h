#ifndef _AudioCore_CuteMixer_h_
#define _AudioCore_CuteMixer_h_

class CuteMidiManager;
class CuteAudioBus;
class CuteMonitor;

class CuteMonitorButton : public Button {
public:
    typedef CuteMonitorButton CLASSNAME;
    CuteMonitorButton();
};

class CuteMixerStrip : public ParentCtrl {
public:
    typedef CuteMixerStrip CLASSNAME;
    CuteMixerStrip();
    void SetTitle(const String& title);
    const String& GetTitle() const;
private:
    String title;
    Label title_label;
};

class CuteMixerRackWidget : public ParentCtrl {
public:
    typedef CuteMixerRackWidget CLASSNAME;
    CuteMixerRackWidget();
    CuteMixerStrip& AddStrip();
private:
    Array<CuteMixerStrip> strips;
};

class CuteMixerRack : public TopWindow {
public:
    typedef CuteMixerRack CLASSNAME;
    CuteMixerRack();
private:
    CuteMixerRackWidget rack_widget;
};

class CuteMixer : public TopWindow {
public:
    typedef CuteMixer CLASSNAME;
    CuteMixer();
    CuteMixerRack& GetRack();
private:
    CuteMixerRack rack;
};

#endif
