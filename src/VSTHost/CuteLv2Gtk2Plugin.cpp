#include "VSTHost.h"

CuteLv2Gtk2Plugin::CuteLv2Gtk2Plugin() {}
bool CuteLv2Gtk2Plugin::Open() { gtk2_editor = true; return true; }
void CuteLv2Gtk2Plugin::Close() { gtk2_editor = false; }
bool CuteLv2Gtk2Plugin::HasGtk2Editor() const { return gtk2_editor; }
