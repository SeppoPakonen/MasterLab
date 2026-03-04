#include "ProjectWindow.h"

CuteRubberBand::CuteRubberBand() : style(1) {}
void CuteRubberBand::SetThickness(int thickness) { this->thickness = thickness; style.SetThickness(thickness); Refresh(); }
int CuteRubberBand::GetThickness() const { return thickness; }
