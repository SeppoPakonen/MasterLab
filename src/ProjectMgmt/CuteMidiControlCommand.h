#ifndef _ProjectMgmt_CuteMidiControlCommand_h_
#define _ProjectMgmt_CuteMidiControlCommand_h_

class CuteMidiControlObserver;

class CuteMidiControlObserverCommand : public CuteCommand {
public:
    CuteMidiControlObserverCommand(const String& name, CuteMidiControlObserver* observer);
protected:
    CuteMidiControlObserver* observer = nullptr;
};

class CuteMidiControlObserverMapCommand : public CuteMidiControlObserverCommand {
public:
    CuteMidiControlObserverMapCommand(CuteMidiControlObserver* observer);
    bool Redo() override;
    bool Undo() override;
};

class CuteMidiControlObserverUnmapCommand : public CuteMidiControlObserverCommand {
public:
    CuteMidiControlObserverUnmapCommand(CuteMidiControlObserver* observer);
    bool Redo() override;
    bool Undo() override;
};

#endif
