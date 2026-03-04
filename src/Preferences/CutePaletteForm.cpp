#include "Preferences.h"

CutePaletteForm::PaletteModel::PaletteModel() { AddColumn("Role"); AddColumn("Color"); }
CutePaletteForm::ColorDelegate::ColorDelegate() {}
CutePaletteForm::ColorButton::ColorButton() {}
CutePaletteForm::ColorEditor::ColorEditor() {}
CutePaletteForm::RoleEditor::RoleEditor() {}
CutePaletteForm::CutePaletteForm() { Add(name_list.TopPos(4,24).HSizePos(4,140)); Add(save_button.SetLabel("Save").TopPos(4,24).RightPos(72,64)); Add(delete_button.SetLabel("Delete").TopPos(4,24).RightPos(4,64)); Add(palette_model.VSizePos(32,0).HSizePos()); SetRect(0,0,640,420); }
void CutePaletteForm::SetPaletteName(const String& palette_name) { this->palette_name = palette_name; }
String CutePaletteForm::GetPaletteName() const { return palette_name; }
bool CutePaletteForm::IsDirty() const { return dirty_count != 0; }
