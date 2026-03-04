#ifndef _ProjectMgmt_CuteMidiEditCommand_h_
#define _ProjectMgmt_CuteMidiEditCommand_h_

class CuteMidiClip;

class CuteMidiEditCommand : public CuteCommand {
public:
    enum CommandType {
        None = 0,
        InsertEvent,
        RemoveEvent,
        UpdateEvent,
        Quantize,
        Transpose,
        Normalize
    };

    CuteMidiEditCommand(const String& name, CuteMidiClip* clip, CommandType command_type);
    bool Redo() override;
    bool Undo() override;
    CommandType GetCommandType() const;

private:
    CuteMidiClip* clip = nullptr;
    CommandType command_type = None;
};

#endif
