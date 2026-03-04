#ifndef _AudioMaster_CuteMessageBox_h_
#define _AudioMaster_CuteMessageBox_h_

class CuteMessageBox : public TopWindow {
public:
    typedef CuteMessageBox CLASSNAME;

    enum Icon { NoIcon = 0, Information = 1, Warning = 2, Critical = 3, Question = 4 };

    CuteMessageBox();

    void SetText(const String& text);
    String GetText() const;

    void SetIcon(Icon icon);
    Icon GetIcon() const;

private:
    Icon icon = NoIcon;
    Label text_label;
};

#endif
