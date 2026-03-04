#ifndef _ProjectMgmt_CuteTimeScaleCommand_h_
#define _ProjectMgmt_CuteTimeScaleCommand_h_

class CuteTimeScale;

class CuteTimeScaleNodeCommand {
public:
    CuteTimeScaleNodeCommand(const String& name, CuteTimeScale* time_scale, int64 frame, double tempo, int beat_type, int beats_per_bar, int beat_divisor);
    virtual ~CuteTimeScaleNodeCommand();

    virtual bool Redo();
    virtual bool Undo();
    CuteTimeScale* GetTimeScale() const;
    int64 GetFrame() const;
    double GetTempo() const;
    int GetBeatType() const;
    int GetBeatsPerBar() const;
    int GetBeatDivisor() const;

protected:
    String name;
    CuteTimeScale* time_scale = nullptr;
    int64 frame = 0;
    double tempo = 120.0;
    int beat_type = 4;
    int beats_per_bar = 4;
    int beat_divisor = 4;
};

class CuteTimeScaleAddNodeCommand : public CuteTimeScaleNodeCommand { public: using CuteTimeScaleNodeCommand::CuteTimeScaleNodeCommand; bool Redo() override; bool Undo() override; };
class CuteTimeScaleUpdateNodeCommand : public CuteTimeScaleNodeCommand { public: using CuteTimeScaleNodeCommand::CuteTimeScaleNodeCommand; bool Redo() override; bool Undo() override; };
class CuteTimeScaleRemoveNodeCommand : public CuteTimeScaleNodeCommand { public: using CuteTimeScaleNodeCommand::CuteTimeScaleNodeCommand; bool Redo() override; bool Undo() override; };
class CuteTimeScaleMoveNodeCommand : public CuteTimeScaleNodeCommand { public: using CuteTimeScaleNodeCommand::CuteTimeScaleNodeCommand; bool Redo() override; bool Undo() override; };

class CuteTimeScaleMarkerCommand {
public:
    CuteTimeScaleMarkerCommand(const String& name, CuteTimeScale* time_scale, int64 frame, const String& text, Color color, int accidentals, int mode);
    virtual ~CuteTimeScaleMarkerCommand();

    virtual bool Redo();
    virtual bool Undo();

protected:
    String name;
    CuteTimeScale* time_scale = nullptr;
    int64 frame = 0;
    String text;
    Color color;
    int accidentals = 0;
    int mode = 0;
};

class CuteTimeScaleAddMarkerCommand : public CuteTimeScaleMarkerCommand { public: using CuteTimeScaleMarkerCommand::CuteTimeScaleMarkerCommand; bool Redo() override; bool Undo() override; };
class CuteTimeScaleUpdateMarkerCommand : public CuteTimeScaleMarkerCommand { public: using CuteTimeScaleMarkerCommand::CuteTimeScaleMarkerCommand; bool Redo() override; bool Undo() override; };
class CuteTimeScaleRemoveMarkerCommand : public CuteTimeScaleMarkerCommand { public: using CuteTimeScaleMarkerCommand::CuteTimeScaleMarkerCommand; bool Redo() override; bool Undo() override; };
class CuteTimeScaleAddKeySignatureCommand : public CuteTimeScaleMarkerCommand { public: using CuteTimeScaleMarkerCommand::CuteTimeScaleMarkerCommand; bool Redo() override; bool Undo() override; };
class CuteTimeScaleUpdateKeySignatureCommand : public CuteTimeScaleMarkerCommand { public: using CuteTimeScaleMarkerCommand::CuteTimeScaleMarkerCommand; bool Redo() override; bool Undo() override; };
class CuteTimeScaleRemoveKeySignatureCommand : public CuteTimeScaleMarkerCommand { public: using CuteTimeScaleMarkerCommand::CuteTimeScaleMarkerCommand; bool Redo() override; bool Undo() override; };

#endif
