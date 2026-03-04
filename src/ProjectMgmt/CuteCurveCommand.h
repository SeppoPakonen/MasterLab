#ifndef _ProjectMgmt_CuteCurveCommand_h_
#define _ProjectMgmt_CuteCurveCommand_h_

class CuteCurve;
class CuteCurveList;

class CuteCurveBaseCommand : public CuteCommand {
public:
    CuteCurveBaseCommand(const String& name);
    bool Redo() override;
    bool Undo() override;
protected:
    virtual bool Execute(bool redo);
};

class CuteCurveCommand : public CuteCurveBaseCommand {
public:
    CuteCurveCommand(const String& name, CuteCurve* curve);
protected:
    CuteCurve* curve = nullptr;
};

class CuteCurveListCommand : public CuteCurveBaseCommand {
public:
    CuteCurveListCommand(const String& name, CuteCurveList* curve_list);
protected:
    CuteCurveList* curve_list = nullptr;
};

class CuteCurveSelectCommand : public CuteCurveListCommand {
public:
    CuteCurveSelectCommand(CuteCurveList* curve_list, CuteCurve* current_curve);
protected:
    bool Execute(bool redo) override;
private:
    CuteCurve* current_curve = nullptr;
};

class CuteCurveModeCommand : public CuteCurveCommand {
public:
    CuteCurveModeCommand(CuteCurve* curve, int mode);
protected:
    bool Execute(bool redo) override;
private:
    int mode = 0;
};

class CuteCurveProcessCommand : public CuteCurveCommand {
public:
    CuteCurveProcessCommand(CuteCurve* curve, bool process);
protected:
    bool Execute(bool redo) override;
private:
    bool process = false;
};

class CuteCurveCaptureCommand : public CuteCurveCommand {
public:
    CuteCurveCaptureCommand(CuteCurve* curve, bool capture);
protected:
    bool Execute(bool redo) override;
private:
    bool capture = false;
};

#endif
