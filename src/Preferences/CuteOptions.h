#ifndef _Preferences_CuteOptions_h_
#define _Preferences_CuteOptions_h_

class CuteOptions {
public:
    CuteOptions();
    void LoadOptions();
    void SaveOptions();
    bool ParseArgs(const Vector<String>& args);
    void ShowError(const String& msg);

    String session_id;
    Vector<String> session_files;
    String messages_font;
    bool messages_limit = false;
    int messages_limit_lines = 1000;
    bool stdout_capture = false;
    bool menubar = true;
    bool statusbar = true;
    bool count_in = false;
    bool metronome = false;
    String session_dir;
};

#endif
