#ifndef _VSTHost_CuteDssiPlugin_h_
#define _VSTHost_CuteDssiPlugin_h_

class CuteDssiPluginType : public CuteLadspaPluginType {
public:
    CuteDssiPluginType();
    bool Open();
    void Close();
    bool HasEditor() const;
private:
    bool has_editor = false;
};

class CuteDssiPlugin : public CuteLadspaPlugin {
public:
    CuteDssiPlugin();
    bool Activate();
    void Deactivate();
    void ProcessEvents();
private:
    bool active = false;
};

#endif
