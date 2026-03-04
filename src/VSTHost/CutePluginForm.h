#ifndef _VSTHost_CutePluginForm_h_
#define _VSTHost_CutePluginForm_h_

class CutePluginParamWidget : public ParentCtrl {
public:
    typedef CutePluginParamWidget CLASSNAME;

    CutePluginParamWidget();

    void SetParam(CutePlugin::Param* param);
    CutePlugin::Param* GetParam() const;
    void Refresh();
    void UpdateParamRange();

private:
    CutePlugin::Param* param = nullptr;
    Label caption;
    SliderCtrl value_slider;
};

class CutePluginForm : public TopWindow {
public:
    typedef CutePluginForm CLASSNAME;

    CutePluginForm();

    void SetPlugin(CutePlugin* plugin);
    CutePlugin* GetPlugin() const;
    void SetPreset(const String& preset);
    const String& GetPreset() const;
    void UpdateActivated();
    void UpdateDirtyCount();
    void UpdateMidiControlAutoConnect();
    void UpdateAuxSendBusName();
    void ToggleEditor();
    void Refresh();
    void Clear();

private:
    void RebuildParamWidgets();

    CutePlugin* plugin = nullptr;
    String preset;
    Array<CutePluginParamWidget> param_widgets;
    ParentCtrl param_area;
};

#endif
