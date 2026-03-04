#ifndef _AudioEditing_CutePasteRepeatForm_h_
#define _AudioEditing_CutePasteRepeatForm_h_

class CuteTimeScale;

class CutePasteRepeatForm : public TopWindow {
public:
    typedef CutePasteRepeatForm CLASSNAME;
    CutePasteRepeatForm();
    void SetRepeatCount(unsigned short repeat_count);
    unsigned short GetRepeatCount() const;
    void SetRepeatPeriod(unsigned long repeat_period);
    unsigned long GetRepeatPeriod() const;
private:
    unsigned short repeat_count = 1;
    unsigned long repeat_period = 0;
    EditInt repeat_count_edit;
    EditInt repeat_period_edit;
    Button ok_button;
    Button cancel_button;
};

#endif
