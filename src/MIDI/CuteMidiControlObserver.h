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
    void SetWidget(Ctrl* widget);
    Ctrl* GetWidget() const;

private:
    CuteSubject* subject = nullptr;
    CuteCurveList* curve_list = nullptr;
    Ctrl* widget = nullptr;
};

#endif
