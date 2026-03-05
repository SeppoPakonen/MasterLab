#ifndef _ProjectMgmt_CuteTrackCommand_h_
#define _ProjectMgmt_CuteTrackCommand_h_

class CuteTrackCommand {
public:
    CuteTrackCommand(const String& name, CuteSession* session);
    virtual ~CuteTrackCommand();

    virtual bool Redo();
    virtual bool Undo();

protected:
    String name;
    CuteSession* session = nullptr;
};

class CuteAddTrackCommand : public CuteTrackCommand {
public:
    CuteAddTrackCommand(CuteSession* session, const String& track_name);
    bool Redo() override;
    bool Undo() override;

private:
    String track_name;
    int track_index = -1;
};

class CuteRemoveTrackCommand : public CuteTrackCommand {
public:
    CuteRemoveTrackCommand(CuteSession* session, int track_index);
    bool Redo() override;
    bool Undo() override;

private:
    int track_index = -1;
    String removed_track_name;
};

class CuteMoveTrackCommand : public CuteTrackCommand {
public:
    CuteMoveTrackCommand(CuteSession* session, int from_index, int to_index);
    bool Redo() override;
    bool Undo() override;

private:
    int from_index = -1;
    int to_index = -1;
};

#endif
