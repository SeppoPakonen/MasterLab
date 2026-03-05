#ifndef _VSTHost_CutePluginScan_h_
#define _VSTHost_CutePluginScan_h_

class CutePluginScan {
public:
    CutePluginScan();

    void SetPluginPaths(const Vector<String>& plugin_paths);
    const Vector<String>& GetPluginPaths() const;
    int RunScan();

private:
    Vector<String> plugin_paths;
};

#endif
