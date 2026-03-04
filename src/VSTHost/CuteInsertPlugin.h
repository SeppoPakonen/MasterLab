#ifndef _VSTHost_CuteInsertPlugin_h_
#define _VSTHost_CuteInsertPlugin_h_

class CuteInsertPluginType {
public:
    CuteInsertPluginType();
    String GetName() const;
private:
    String name;
};

class CuteAudioInsertPluginType : public CuteInsertPluginType { };
class CuteMidiInsertPluginType : public CuteInsertPluginType { };

class CuteInsertPlugin {
public:
    class Param {
    public:
        Param();
        void SetName(const String& name);
        const String& GetName() const;
    private:
        String name;
    };

    CuteInsertPlugin();
    virtual ~CuteInsertPlugin();
    bool Open();
    void Close();
private:
    bool opened = false;
};

class CuteAudioInsertPlugin : public CuteInsertPlugin { };
class CuteMidiInsertPlugin : public CuteInsertPlugin { };

class CuteAuxSendPluginType : public CuteInsertPluginType { };
class CuteAudioAuxSendPluginType : public CuteAuxSendPluginType { };
class CuteMidiAuxSendPluginType : public CuteAuxSendPluginType { };
class CuteAuxSendPlugin : public CuteInsertPlugin { };
class CuteAudioAuxSendPlugin : public CuteAuxSendPlugin { };
class CuteMidiAuxSendPlugin : public CuteAuxSendPlugin { };

#endif
