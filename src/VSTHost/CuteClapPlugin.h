#ifndef _VSTHost_CuteClapPlugin_h_
#define _VSTHost_CuteClapPlugin_h_

class CuteClapPluginType {
public:
    CuteClapPluginType();
    bool Open();
    void Close();
    String GetName() const;
private:
    String name;
};

class CuteClapPlugin {
public:
    CuteClapPlugin();
    bool Open();
    void Close();
    bool Activate();
    void Deactivate();
    void Process();
    String GetLabel() const;
private:
    String label;
    bool active = false;
};

#endif
