#ifndef _ProjectMgmt_CuteClipCommand_h_
#define _ProjectMgmt_CuteClipCommand_h_

class CuteClip;
class CuteTrack;
class CuteClipCommand : public CuteCommand {
public:
    struct Item {
        CuteClip* clip = nullptr;
        CuteTrack* track = nullptr;
        bool auto_delete = false;
    };

    CuteClipCommand(const String& name);
    ~CuteClipCommand();
    void AddClip(CuteClip* clip, CuteTrack* track);
    bool Redo() override;
    bool Undo() override;

private:
    Vector<Item> items;
};

#endif
