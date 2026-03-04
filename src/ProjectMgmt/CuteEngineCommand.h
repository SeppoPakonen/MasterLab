#ifndef _ProjectMgmt_CuteEngineCommand_h_
#define _ProjectMgmt_CuteEngineCommand_h_

class CuteBus;

class CuteBusCommand : public CuteCommand {
public:
    CuteBusCommand(const String& name, CuteBus* bus);
protected:
    CuteBus* bus = nullptr;
};

class CuteCreateBusCommand : public CuteBusCommand {
public:
    CuteCreateBusCommand(CuteBus* bus);
    bool Redo() override;
    bool Undo() override;
};

class CuteUpdateBusCommand : public CuteBusCommand {
public:
    CuteUpdateBusCommand(CuteBus* bus);
    bool Redo() override;
    bool Undo() override;
};

class CuteDeleteBusCommand : public CuteBusCommand {
public:
    CuteDeleteBusCommand(CuteBus* bus);
    bool Redo() override;
    bool Undo() override;
};

class CuteMoveBusCommand : public CuteBusCommand {
public:
    CuteMoveBusCommand(CuteBus* bus, int delta);
    bool Redo() override;
    bool Undo() override;
private:
    int delta = 0;
};

class CuteBusMonitorCommand : public CuteBusCommand {
public:
    CuteBusMonitorCommand(CuteBus* bus, bool monitor);
    bool Redo() override;
    bool Undo() override;
private:
    bool monitor = false;
};

class CuteBusGainCommand : public CuteBusCommand {
public:
    CuteBusGainCommand(CuteBus* bus, double gain);
    bool Redo() override;
    bool Undo() override;
private:
    double gain = 1.0;
};

class CuteBusPanningCommand : public CuteBusCommand {
public:
    CuteBusPanningCommand(CuteBus* bus, double panning);
    bool Redo() override;
    bool Undo() override;
private:
    double panning = 0.0;
};

#endif
