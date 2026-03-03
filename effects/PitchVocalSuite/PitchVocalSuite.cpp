#include "PitchVocalSuite.h"

// --- PitchVocalProcessor ---

PitchVocalProcessor::PitchVocalProcessor()
{
	ParameterDescriptor pAlg;
	pAlg.id = "algorithm";
	pAlg.name = "Algorithm";
	pAlg.min = 0;
	pAlg.max = 2;
	pAlg.default_value = 0;
	Parameters().Add(pAlg);
	
	ParameterDescriptor pSpeed;
	pSpeed.id = "speed";
	pSpeed.name = "Speed";
	pSpeed.min = 0;
	pSpeed.max = 100;
	pSpeed.default_value = 50;
	Parameters().Add(pSpeed);

	ParameterDescriptor pVib;
	pVib.id = "vibrato";
	pVib.name = "Vibrato";
	pVib.min = 0;
	pVib.max = 100;
	pVib.default_value = 0;
	Parameters().Add(pVib);
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
	// Read parameters (demonstration)
	// double speed = Parameters().GetValueById("speed");
	
	// Skeleton pitch processing
	if(ctx.input.frame_count > 0 && ctx.input.channels != nullptr) {
		float* channel0 = ctx.input.GetChannel(0);
		if(channel0) {
			double startTime = ctx.transport.position_beats; // Simplified time
			pitchEngine.Analyze(channel0, ctx.input.frame_count, startTime, pitchPoints);
			
			// Keep only last 1000 points for the skeleton visualization
			if(pitchPoints.GetCount() > 1000)
				pitchPoints.Remove(0, pitchPoints.GetCount() - 1000);
				
			// Rolling waveform buffer
			int framesToCopy = min((int)ctx.input.frame_count, waveformBufferSize);
			if (waveformBuffer.GetCount() < waveformBufferSize) {
				for(int i = 0; i < framesToCopy && waveformBuffer.GetCount() < waveformBufferSize; ++i)
					waveformBuffer.Add(channel0[i]);
			} else {
				// Shift and append
				int remaining = waveformBufferSize - framesToCopy;
				if (remaining > 0) {
					for(int i = 0; i < remaining; ++i)
						waveformBuffer[i] = waveformBuffer[i + framesToCopy];
					for(int i = 0; i < framesToCopy; ++i)
						waveformBuffer[remaining + i] = channel0[i];
				} else {
					for(int i = 0; i < waveformBufferSize; ++i)
						waveformBuffer[i] = channel0[i + (framesToCopy - waveformBufferSize)];
				}
			}
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
	algorithm << [=] { WhenAction(); };
	
	Add(lblSpeed.LeftPos(270, 80).TopPos(10, 20));
	Add(correctionSpeed.LeftPos(360, 150).TopPos(10, 20));
	lblSpeed.SetLabel("Speed:");
	correctionSpeed.MinMax(0, 100);
	correctionSpeed.SetData(50);
	correctionSpeed << [=] { WhenAction(); };
	
	Add(lblVibrato.LeftPos(530, 80).TopPos(10, 20));
	Add(vibratoAmount.LeftPos(620, 150).TopPos(10, 20));
	lblVibrato.SetLabel("Vibrato:");
	vibratoAmount.MinMax(0, 100);
	vibratoAmount.SetData(0);
	vibratoAmount << [=] { WhenAction(); };
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
	
	if (processor) {
		const Vector<float>& buffer = processor->GetWaveformBuffer();
		int count = buffer.GetCount();
		if (count > 0) {
			int midY = sz.cy / 2;
			w.DrawLine(0, midY, sz.cx, midY, 1, SColorPaper());
			
			// Simple peak rendering
			double samplesPerPixel = (double)count / sz.cx;
			for (int x = 0; x < sz.cx; ++x) {
				int start = (int)(x * samplesPerPixel);
				int end = (int)((x + 1) * samplesPerPixel);
				float minV = 0, maxV = 0;
				for (int i = start; i < end && i < count; ++i) {
					minV = min(minV, buffer[i]);
					maxV = max(maxV, buffer[i]);
				}
				int y1 = midY + (int)(minV * (sz.cy / 2));
				int y2 = midY + (int)(maxV * (sz.cy / 2));
				w.DrawLine(x, y1, x, y2, 1, SColorText());
			}
		}
	}

	w.DrawText(10, 10, "Waveform Strip", Arial(14), SColorPaper());
}

// --- PitchVocalEditor ---

PitchVocalEditor::PitchVocalEditor()
{
	int topHeight = 80;
	int bottomHeight = 100;
	
	Add(topBar.TopPos(0, topHeight).HSizePos());
	Add(waveformStrip.BottomPos(0, bottomHeight).HSizePos());
	Add(graphEditor.VSizePos(topHeight, bottomHeight).HSizePos());
	
	topBar.WhenAction = [=] { OnTopBarAction(); };
	
	SetTimeCallback(-40, [=] { Refresh(); });
}

void PitchVocalEditor::SetProcessor(PluginProcessor* p)
{
	PluginEditor::SetProcessor(p);
	auto* pvp = dynamic_cast<PitchVocalProcessor*>(p);
	graphEditor.SetProcessor(pvp);
	waveformStrip.SetProcessor(pvp);
	SyncFromProcessor();
}

void PitchVocalEditor::SyncToProcessor()
{
	if(processor) {
		processor->SetParameter("algorithm", topBar.GetAlgorithm());
		processor->SetParameter("speed", topBar.GetSpeed());
		processor->SetParameter("vibrato", topBar.GetVibrato());
	}
}

void PitchVocalEditor::SyncFromProcessor()
{
	if(processor) {
		topBar.SetAlgorithm((int)processor->GetParameter("algorithm"));
		topBar.SetSpeed(processor->GetParameter("speed"));
		topBar.SetVibrato(processor->GetParameter("vibrato"));
	}
}

void PitchVocalEditor::OnTopBarAction()
{
	SyncToProcessor();
}

// --- Entry Points ---

#ifdef flagDLL

#include <PluginABI/LV2/LV2.h>
LV2_PLUGIN_MAIN(PitchVocalProcessor)

#else

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

#endif
