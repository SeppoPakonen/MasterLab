#ifndef _VSTHost_CuteLadspaPlugin_h_
#define _VSTHost_CuteLadspaPlugin_h_

class CutePluginFile;

class CuteLadspaPluginType {
public:
    CuteLadspaPluginType();
    bool Open();
    void Close();
    String GetLabel() const;
private:
    String label;
};

class CuteLadspaPlugin {
public:
    class Param {
    public:
        Param();
        void SetValue(float value);
        float GetValue() const;
    private:
        float value = 0.0f;
    };

    CuteLadspaPlugin();
    bool Open();
    void Close();
    void Process();
    String GetName() const;
private:
    String name;
};

#endif
