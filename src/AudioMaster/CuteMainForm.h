#ifndef _AudioMaster_CuteMainForm_h_
#define _AudioMaster_CuteMainForm_h_

class CuteFileSystem;
class CuteFiles;
class CuteMessages;
class CuteConnections;
class CuteInstrumentMenu;

class CuteMainForm : public TopWindow {
public:
    typedef CuteMainForm CLASSNAME;

    CuteMainForm();
    ~CuteMainForm();

    static CuteMainForm* GetInstance();

    void Setup();
    void ClearFilename();
    void UpdateTransportTime(unsigned long play_head);
    void AppendMessages(const String& text);
    void AppendMessagesError(const String& text);

    CuteFileSystem* GetFileSystem() const;
    CuteFiles* GetFiles() const;
    CuteConnections* GetConnections() const;

private:
    static CuteMainForm* instance;
    String filename;
    Label status_label;
    Splitter split;
    ParentCtrl workspace;
    CuteMessages* messages = nullptr;
    CuteFileSystem* file_system = nullptr;
    CuteFiles* files = nullptr;
    CuteConnections* connections = nullptr;
};

#endif
