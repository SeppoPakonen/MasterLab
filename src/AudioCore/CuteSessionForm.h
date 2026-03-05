#ifndef _AudioCore_CuteSessionForm_h_
#define _AudioCore_CuteSessionForm_h_

#ifdef flagGUI

class CuteSessionForm : public TopWindow {
public:
    typedef CuteSessionForm CLASSNAME;

    CuteSessionForm();

    void SetSession(CuteSession* session, bool session_dir_enabled);
    const CuteSession::Properties& GetProperties() const;
    bool IsSessionDirEnabled() const;

private:
    CuteSession* session = nullptr;
    CuteSession::Properties properties;
    bool session_dir_enabled = false;
    EditString session_dir;
    EditString session_name;
    DocEdit description;
};

#endif

#endif
