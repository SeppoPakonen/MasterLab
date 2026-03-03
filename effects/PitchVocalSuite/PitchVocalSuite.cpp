#include "PitchVocalSuite.h"

// --- PitchVocalTopBar ---

PitchVocalTopBar::PitchVocalTopBar()
{
}

void PitchVocalTopBar::Paint(Draw& w)
{
	Size sz = GetSize();
	w.DrawRect(sz, SColorShadow());
	w.DrawText(10, 10, "Global Controls Placeholder (Algorithm, Speed, Vibrato)", Arial(20), SColorPaper());
}

// --- PitchGraphEditor ---

PitchGraphEditor::PitchGraphEditor()
{
}

void PitchGraphEditor::Paint(Draw& w)
{
	Size sz = GetSize();
	w.DrawRect(sz, SColorPaper());
	
	// Draw a simple grid
	int step = 40;
	for(int i = step; i < sz.cy; i += step)
		w.DrawLine(0, i, sz.cx, i, 1, SColorDisabled());
	for(int i = step; i < sz.cx; i += step)
		w.DrawLine(i, 0, i, sz.cy, 1, SColorDisabled());

	w.DrawText(sz.cx / 2 - 100, sz.cy / 2 - 10, "Pitch Graph Editor (Custom Ctrl)", Arial(24), SColorText());
}

// --- WaveformStrip ---

WaveformStrip::WaveformStrip()
{
}

void WaveformStrip::Paint(Draw& w)
{
	Size sz = GetSize();
	w.DrawRect(sz, SColorShadow());
	
	// Draw a dummy waveform
	w.DrawLine(0, sz.cy / 2, sz.cx, sz.cy / 2, 2, SColorPaper());
	for(int i = 0; i < sz.cx; i += 5) {
		int h = (int)(sin(i * 0.1) * (sz.cy / 3));
		w.DrawLine(i, sz.cy / 2 - h, i, sz.cy / 2 + h, 1, SColorText());
	}

	w.DrawText(10, 10, "Waveform Strip (Custom Ctrl)", Arial(20), SColorPaper());
}

// --- PitchVocalEditor ---

PitchVocalEditor::PitchVocalEditor()
{
	int topHeight = 80;
	int bottomHeight = 100;
	
	Add(topBar.TopPos(0, topHeight).HSizePos());
	Add(waveformStrip.BottomPos(0, bottomHeight).HSizePos());
	Add(graphEditor.VSizePos(topHeight, bottomHeight).HSizePos());
}

// --- Standalone Main ---

GUI_APP_MAIN
{
	PitchVocalEditor editor;
	PluginWindow win;
	win.Title("PitchVocalSuite Standalone");
	win.SetEditor(editor);
	win.Run();
}
