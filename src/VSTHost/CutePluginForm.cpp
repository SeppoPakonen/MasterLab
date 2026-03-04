#include "VSTHost.h"

CutePluginParamWidget::CutePluginParamWidget() { Add(caption.LeftPosZ(0, 160).VSizePos()); Add(value_slider.HSizePosZ(168, 0).VCenterPosZ(24)); }
void CutePluginParamWidget::SetParam(CutePlugin::Param* param) { this->param = param; Refresh(); }
CutePlugin::Param* CutePluginParamWidget::GetParam() const { return param; }
void CutePluginParamWidget::Refresh() { if (!param) return; caption.SetLabel(param->GetName()); value_slider.MinMax((int)param->GetMinValue(), (int)param->GetMaxValue()); value_slider.SetData((int)param->GetValue()); }
void CutePluginParamWidget::UpdateParamRange() { if (!param) return; value_slider.MinMax((int)param->GetMinValue(), (int)param->GetMaxValue()); }

CutePluginForm::CutePluginForm() { Title("Cute Plugin"); Sizeable().Zoomable(); Add(param_area.SizePos()); }
void CutePluginForm::SetPlugin(CutePlugin* plugin) { this->plugin = plugin; RebuildParamWidgets(); }
CutePlugin* CutePluginForm::GetPlugin() const { return plugin; }
void CutePluginForm::SetPreset(const String& preset) { this->preset = preset; }
const String& CutePluginForm::GetPreset() const { return preset; }
void CutePluginForm::UpdateActivated() {}
void CutePluginForm::UpdateDirtyCount() {}
void CutePluginForm::UpdateMidiControlAutoConnect() {}
void CutePluginForm::UpdateAuxSendBusName() {}
void CutePluginForm::ToggleEditor() { if (!plugin) return; if (plugin->IsEditorVisible()) plugin->CloseEditor(); else plugin->OpenEditor(); }
void CutePluginForm::Refresh() { for (int i = 0; i < param_widgets.GetCount(); ++i) param_widgets[i].Refresh(); }
void CutePluginForm::Clear() { param_widgets.Clear(); plugin = nullptr; preset.Clear(); }
void CutePluginForm::RebuildParamWidgets() { param_widgets.Clear(); if (!plugin) return; for (int i = 0; i < plugin->GetParams().GetCount(); ++i) { CutePluginParamWidget& widget = param_widgets.Add(); widget.SetParam(&plugin->GetParams()[i]); param_area.Add(widget.HSizePosZ(8, 8).TopPosZ(8 + (i * 28), 24)); } }
