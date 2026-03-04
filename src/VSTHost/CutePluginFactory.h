#ifndef _VSTHost_CutePluginFactory_h_
#define _VSTHost_CutePluginFactory_h_

class CuteDummyPluginType;

class CutePluginFactory {
public:
    class Scanner {
    public:
        Scanner();

        bool Open();
        void Close();
        void AddTypes(Vector<CutePluginType*>& type_list) const;
        const Vector<String>& GetFiles() const;
        const VectorMap<String, String>& GetDummyPluginMap() const;

    private:
        Vector<String> files;
        VectorMap<String, String> dummy_plugin_map;
        bool is_open = false;
    };

    CutePluginFactory();

    void SetTypeHint(CutePluginType::Hint type_hint);
    CutePluginType::Hint GetTypeHint() const;
    void SetRescan(bool rescan);
    bool IsRescan() const;
    int Scan();
    const Array<CutePluginType>& GetTypes() const;
    CutePluginType& AddType();
    void Clear();
    void ClearAll();
    Vector<String>& GetPluginPaths();
    const Vector<String>& GetPluginPaths() const;
    void UpdatePluginPaths(const Vector<String>& plugin_paths);
    void SetBlacklist(const Index<String>& blacklist);
    const Index<String>& GetBlacklist() const;
    static CutePluginFactory& Get();

private:
    CutePluginType::Hint type_hint = CutePluginType::Any;
    bool rescan = false;
    Array<CutePluginType> types;
    Vector<String> plugin_paths;
    Index<String> blacklist;
};

class CuteDummyPluginType : public CutePluginType {
public:
    CuteDummyPluginType();

    bool Open();
    void Close();
    String GetFilename() const;
};

#endif
