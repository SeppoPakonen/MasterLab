#ifndef _VSTHost_CuteLv2Plugin_h_
#define _VSTHost_CuteLv2Plugin_h_

class CuteLv2PluginType {
public:
    CuteLv2PluginType();
    bool Open();
    void Close();
    String GetUri() const;
private:
    String uri;
};

class CuteLv2Plugin {
public:
    class Param {
    public:
        Param();
        void SetValue(float value);
        float GetValue() const;
    private:
        float value = 0.0f;
    };

    class Property {
    public:
        Property();
        void SetKey(const String& key);
        const String& GetKey() const;
        void SetValue(const Value& value);
        const Value& GetValue() const;
    private:
        String key;
        Value value;
    };

    CuteLv2Plugin();
    bool Open();
    void Close();
    void Activate();
    void Deactivate();
    void Process();

private:
    bool active = false;
};

#endif
