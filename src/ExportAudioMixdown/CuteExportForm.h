#ifndef _ExportAudioMixdown_CuteExportForm_h_
#define _ExportAudioMixdown_CuteExportForm_h_

class CuteSession;

class CuteExportForm : public TopWindow {
public:
    typedef CuteExportForm CLASSNAME;

    enum RangeType { Session = 0, Loop = 1, Punch = 2, Edit = 3, Custom = 4 };

    CuteExportForm();
    virtual ~CuteExportForm();

    void SetSession(CuteSession* session);
    CuteSession* GetSession() const;

    void SetRangeType(RangeType range_type);
    RangeType GetRangeType() const;

    void SetOutputPath(const String& output_path);
    const String& GetOutputPath() const;

protected:
    void BuildLayout();

    CuteSession* session = nullptr;
    RangeType range_type = Session;
    String output_path;
    DropList range_list;
    EditString path_edit;
    Button browse_button;
    Button export_button;
    Button cancel_button;
};

class CuteExportTrackForm : public CuteExportForm {
public:
    typedef CuteExportTrackForm CLASSNAME;
    CuteExportTrackForm();
};

class CuteExportClipForm : public CuteExportForm {
public:
    typedef CuteExportClipForm CLASSNAME;
    CuteExportClipForm();
};

#endif
