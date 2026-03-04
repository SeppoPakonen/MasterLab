#ifndef _ProjectMgmt_CuteSessionCommand_h_
#define _ProjectMgmt_CuteSessionCommand_h_

class CuteSession;

class CuteSessionCommand {
public:
    CuteSessionCommand(const String& name, CuteSession* session);
    virtual ~CuteSessionCommand();

    const String& GetName() const;
    CuteSession* GetSession() const;
    virtual bool Redo();
    virtual bool Undo();

protected:
    String name;
    CuteSession* session = nullptr;
};

class CuteSessionLoopCommand : public CuteSessionCommand {
public:
    CuteSessionLoopCommand(CuteSession* session, int64 start_frame, int64 end_frame);
    bool Redo() override;
    bool Undo() override;

private:
    int64 start_frame = 0;
    int64 end_frame = 0;
};

class CuteSessionPunchCommand : public CuteSessionCommand {
public:
    CuteSessionPunchCommand(CuteSession* session, int64 start_frame, int64 end_frame);
    bool Redo() override;
    bool Undo() override;

private:
    int64 start_frame = 0;
    int64 end_frame = 0;
};

class CuteSessionEditCommand : public CuteSessionCommand {
public:
    CuteSessionEditCommand(CuteSession* session, const CuteSession::Properties& properties);
    bool Redo() override;
    bool Undo() override;

private:
    CuteSession::Properties before_properties;
    CuteSession::Properties after_properties;
};

#endif
