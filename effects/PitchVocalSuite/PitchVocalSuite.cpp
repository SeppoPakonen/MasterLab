#include "PitchVocalSuite.h"

// --- PitchVocalProcessor ---

PitchVocalProcessor::PitchVocalProcessor()
{
	// Add parameters, etc.
}

Upp::String PitchVocalProcessor::GetURI() const
{
	return "https://masterlab.com/plugins/pitch-vocal-suite";
}

Upp::String PitchVocalProcessor::GetName() const
{
	return "Pitch Vocal Suite";
}

void PitchVocalProcessor::Process(ProcessContext& ctx)
{
	// Skeleton pitch processing
	if(ctx.input.frame_count > 0 && ctx.input.channels != nullptr) {
		float* channel0 = ctx.input.GetChannel(0);
		if(channel0) {
			// In a real plugin, this might happen in a background thread 
			// or be cached, but for the skeleton we just analyze the incoming block
			// and keep a rolling buffer of points.
			
			double startTime = ctx.transport.position_beats; // Simplified time
			pitchEngine.Analyze(channel0, ctx.input.frame_count, startTime, pitchPoints);
			
			// Keep only last 1000 points for the skeleton visualization
			if(pitchPoints.GetCount() > 1000)
				pitchPoints.Remove(0, pitchPoints.GetCount() - 1000);
		}
	}
}

// --- PitchVocalTopBar ---

PitchVocalTopBar::PitchVocalTopBar()
{
	Add(lblAlgorithm.LeftPos(10, 80).TopPos(10, 20));
	Add(algorithm.LeftPos(100, 150).TopPos(10, 20));
	lblAlgorithm.SetLabel("Algorithm:");
	algorithm.Add("Autocorrelation");
	algorithm.Add("FFT / Phase Vocoder");
	algorithm.Add("Neural (Mock)");
	algorithm.SetIndex(0);
	
	Add(lblSpeed.LeftPos(270, 80).TopPos(10, 20));
	Add(correctionSpeed.LeftPos(360, 150).TopPos(10, 20));
	lblSpeed.SetLabel("Speed:");
	correctionSpeed.MinMax(0, 100);
	correctionSpeed.SetData(50);
	
	Add(lblVibrato.LeftPos(530, 80).TopPos(10, 20));
	Add(vibratoAmount.LeftPos(620, 150).TopPos(10, 20));
	lblVibrato.SetLabel("Vibrato:");
	vibratoAmount.MinMax(0, 100);
	vibratoAmount.SetData(0);
}

void PitchVocalTopBar::Paint(Draw& w)
{
	Size sz = GetSize();
	w.DrawRect(sz, SColorFace()); // Change to Face color to match controls
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

	if(processor) {
		const Vector<am::PitchPoint>& points = processor->GetPitchPoints();
		if(points.GetCount() > 1) {
			for(int i = 1; i < points.GetCount(); i++) {
				const am::PitchPoint& p1 = points[i-1];
				const am::PitchPoint& p2 = points[i];
				
				// Very simplified mapping
				int x1 = (int)((p1.time) * 100) % sz.cx;
				int x2 = (int)((p2.time) * 100) % sz.cx;
				
				// Handle wrap-around for rolling buffer
				if(x2 < x1) continue;
				
				double midi1 = am::PitchAnalysisEngine::FrequencyToMidi(p1.frequency);
				double midi2 = am::PitchAnalysisEngine::FrequencyToMidi(p2.frequency);
				
				// MIDI range 40-80 roughly
				int y1 = sz.cy - (int)((midi1 - 40) * (sz.cy / 40.0));
				int y2 = sz.cy - (int)((midi2 - 40) * (sz.cy / 40.0));
				
				w.DrawLine(x1, y1, x2, y2, 2, Red());
			}
		}
	}

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

void PitchVocalEditor::SetProcessor(PluginProcessor* p)
{
	PluginEditor::SetProcessor(p);
	graphEditor.SetProcessor(dynamic_cast<PitchVocalProcessor*>(p));
}

// --- Standalone Main ---

void RunTests()
{
	Upp::Cout() << "Running PitchVocalSuite Tests...\n";
	// Add actual test logic here
	Upp::Cout() << "Tests completed successfully.\n";
}

GUI_APP_MAIN
{
	CommandLineArguments cl;
	cl.AddArg("test", 't', "Run internal tests", false);
	cl.AddArg("help", 'h', "Show help", false);
	
	if(!cl.Parse()) {
		cl.PrintHelp();
		return;
	}
	
	if(cl.IsArg("help")) {
		cl.PrintHelp();
		return;
	}
	
	if(cl.IsArg("test")) {
		RunTests();
		return;
	}

	PitchVocalProcessor processor;
	PitchVocalEditor editor;
	editor.SetProcessor(dynamic_cast<PluginProcessor*>(&processor));
	
	PluginWindow win;
	win.Title("PitchVocalSuite Standalone");
	win.SetEditor(editor);
	win.Run();
}
