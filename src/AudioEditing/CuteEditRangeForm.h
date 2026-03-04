#ifndef _AudioEditing_CuteEditRangeForm_h_
#define _AudioEditing_CuteEditRangeForm_h_

class CuteSession;

class CuteEditRangeForm : public TopWindow {
public:
    typedef CuteEditRangeForm CLASSNAME;

    enum RangeType { Session = 0, Loop = 1, Punch = 2, Edit = 3, Custom = 4 };

    CuteEditRangeForm();

    void SetSession(CuteSession* session);
    CuteSession* GetSession() const;

    void SetRangeType(RangeType range_type);
    RangeType GetRangeType() const;

    void SetStartFrame(int64 start_frame);
    int64 GetStartFrame() const;

    void SetEndFrame(int64 end_frame);
    int64 GetEndFrame() const;

private:
    void BuildLayout();

    CuteSession* session = nullptr;
    RangeType range_type = Session;
    int64 start_frame = 0;
    int64 end_frame = 0;
    DropList range_list;
    EditInt64 start_edit;
    EditInt64 end_edit;
    Button ok_button;
    Button cancel_button;
};

#endif
