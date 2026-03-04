#ifndef _TransportUI_CuteSpinBox_h_
#define _TransportUI_CuteSpinBox_h_

class CuteSpinBox : public EditDoubleSpin {
public:
    typedef CuteSpinBox CLASSNAME;

    enum EditMode {
        DefaultMode = 0,
        DeferredMode,
    };

    CuteSpinBox();

    void SetEditMode(EditMode edit_mode);
    EditMode GetEditMode() const;

private:
    EditMode edit_mode = DefaultMode;
};

class CuteTimeSpinBox : public EditString {
public:
    typedef CuteTimeSpinBox CLASSNAME;

    CuteTimeSpinBox();

    void SetTimeScale(CuteTimeScale* time_scale);
    CuteTimeScale* GetTimeScale() const;
    void SetDisplayFormat(int display_format);
    int GetDisplayFormat() const;
    void UpdateDisplayFormat();
    void SetValue(int64 value);
    int64 GetValue() const;

private:
    CuteTimeScale* time_scale = nullptr;
    int display_format = 0;
    int64 value = 0;
};

class CuteTempoSpinBox : public EditString {
public:
    typedef CuteTempoSpinBox CLASSNAME;

    CuteTempoSpinBox();

    void SetTempo(double tempo);
    double GetTempo() const;
    void SetBeatsPerBar(int beats_per_bar);
    int GetBeatsPerBar() const;
    void SetBeatDivisor(int beat_divisor);
    int GetBeatDivisor() const;

private:
    double tempo = 120.0;
    int beats_per_bar = 4;
    int beat_divisor = 4;
};

#endif
