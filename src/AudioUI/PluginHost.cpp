#include "PluginHost.h"

namespace am {
namespace UI {

PluginHost::PluginHost()
{
}

void PluginHost::SetPlugin(PluginProcessor& p, PluginEditor& e)
{
	processor = &p;
	editor = &e;
	
	editor->SetProcessor(processor);
	Add(*editor);
	
	Refresh();
}

void PluginHost::Paint(Draw& w)
{
	Size sz = GetSize();
	int headerHeight = 25;
	
	// Draw host frame
	w.DrawRect(0, 0, sz.cx, headerHeight, SColorFace());
	w.DrawRect(0, headerHeight, sz.cx, sz.cy - headerHeight, SColorPaper());
	w.DrawRect(0, 0, sz.cx, sz.cy, SColorDisabled()); // Frame border

	// Standard text for name/bypass
	w.DrawText(5, 5, "Plugin Host: " + pluginName, Arial(12).Bold(), SColorText());
}

void PluginHost::Layout()
{
	if(editor) {
		int headerHeight = 25;
		editor->HSizePos(2, 2).VSizePos(headerHeight, 2);
	}
}

} // namespace UI
} // namespace am
