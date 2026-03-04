#ifndef _VSTHost_CutePluginSelectForm_h_
#define _VSTHost_CutePluginSelectForm_h_

class CutePluginSelectForm : public TopWindow {
public:
    typedef CutePluginSelectForm CLASSNAME;

    CutePluginSelectForm();

    void SetPluginList(CutePluginList* plugin_list);
    CutePluginList* GetPluginList() const;
    int GetPluginCount() const;
    String GetPluginFilename() const;
    int GetPluginIndex() const;
    CutePluginType::Hint GetPluginTypeHint() const;

private:
    CutePluginList* plugin_list = nullptr;
    ArrayCtrl plugin_table;
};

#endif
