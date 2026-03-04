#ifndef _MIDI_CuteMidiControlPluginWidget_h_
#define _MIDI_CuteMidiControlPluginWidget_h_

class CuteMidiControlTypeGroup;
class CuteMidiControlPlugin;

class CuteMidiControlPluginWidget : public ParentCtrl {
public:
    typedef CuteMidiControlPluginWidget CLASSNAME;

    CuteMidiControlPluginWidget();
    void SetPlugin(CuteMidiControlPlugin* plugin);
    CuteMidiControlPlugin* GetPlugin() const;

private:
    CuteMidiControlPlugin* plugin = nullptr;
    Label name_label;
    ArrayCtrl mapping_list;
};

#endif
