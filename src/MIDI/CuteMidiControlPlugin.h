#ifndef _MIDI_CuteMidiControlPlugin_h_
#define _MIDI_CuteMidiControlPlugin_h_

class CuteMidiBus;

class CuteMidiControlPluginType {
public:
    CuteMidiControlPluginType();
    String GetName() const;
private:
    String name;
};

class CuteMidiControlPlugin {
public:
    class Param {
    public:
        Param();
        void SetValue(float value);
        float GetValue() const;
    private:
        float value = 0.0f;
    };

    CuteMidiControlPlugin();
    bool Open();
    void Close();
    void Process();

private:
    bool opened = false;
};

#endif
