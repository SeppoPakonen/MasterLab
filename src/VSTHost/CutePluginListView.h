#ifndef _VSTHost_CutePluginListView_h_
#define _VSTHost_CutePluginListView_h_

class CutePluginListItem : public ParentCtrl {
public:
    typedef CutePluginListItem CLASSNAME;

    CutePluginListItem();

    void SetPlugin(CutePlugin* plugin);
    CutePlugin* GetPlugin() const;
    void SetPluginForm(CutePluginForm* plugin_form);
    CutePluginForm* GetPluginForm() const;
    void UpdateActivated();
    void SetDirectAccessWidth(int direct_access_width);
    int GetDirectAccessWidth() const;

private:
    CutePlugin* plugin = nullptr;
    CutePluginForm* plugin_form = nullptr;
    int direct_access_width = 120;
    Label caption;
    Option activated;
};

class CutePluginListView : public ArrayCtrl {
public:
    typedef CutePluginListView CLASSNAME;

    enum DragState {
        DragNone = 0,
        DragDirectAccess,
    };

    CutePluginListView();

    void SetPluginList(CutePluginList* plugin_list);
    CutePluginList* GetPluginList() const;
    void SetTinyScrollBar(bool tiny_scroll_bar);
    bool IsTinyScrollBar() const;
    void Refresh();
    void Clear();
    CutePluginListItem* GetPluginItem(int index);
    static void InsertPluginBus(CutePluginList& plugin_list, CutePlugin& plugin);
    static void UpdateAuxSendPluginBus(CutePluginList& plugin_list, const String& bus_name);
    void AddPlugin();
    void RemovePlugin();
    void MoveUpPlugin();
    void MoveDownPlugin();

private:
    CutePluginList* plugin_list = nullptr;
    bool tiny_scroll_bar = false;
    DragState drag_state = DragNone;
    Array<CutePluginListItem> items;
};

#endif
