#ifndef _Preferences_CuteOptionsForm_h_
#define _Preferences_CuteOptionsForm_h_

class CuteOptions;
class CuteTimeScale;

class CuteOptionsForm : public TopWindow {
public:
    typedef CuteOptionsForm CLASSNAME;
    CuteOptionsForm();
    void SetOptions(CuteOptions* options);
    CuteOptions* GetOptions() const;
    bool IsDirtyMeterColors() const;
    bool IsDirtyCustomColorThemes() const;

private:
    CuteOptions* options = nullptr;
    int dirty_count = 0;
    int dirty_meter_colors = 0;
    int dirty_custom_color_themes = 0;
    TabCtrl tabs;
    Button ok_button;
    Button cancel_button;
};

#endif
