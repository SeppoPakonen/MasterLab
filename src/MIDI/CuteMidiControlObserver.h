#ifndef _MIDI_CuteMidiControlObserver_h_
#define _MIDI_CuteMidiControlObserver_h_

class CuteCurveList;

class CuteMidiControlObserver {
public:
    CuteMidiControlObserver();
    virtual ~CuteMidiControlObserver();

    void SetSubject(CuteSubject* subject);
    CuteSubject* GetSubject() const;
    void SetCurveList(CuteCurveList* curve_list);
    CuteCurveList* GetCurveList() const;
    void SetWidget(Upp::Ctrl* widget);
    Upp::Ctrl* GetWidget() const;

private:
    CuteSubject* subject = nullptr;
    CuteCurveList* curve_list = nullptr;
    Upp::Ctrl* widget = nullptr;
};

#endif
