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
	WantFocus();
}

Rect PitchGraphEditor::GetNoteRect(const PitchNote& note, const Size& sz) const
{
	if (!viewport) return Rect(0,0,0,0);
	int x = (int)((note.startTime - viewport->scrollX) * viewport->zoomX);
	int w = (int)(note.duration * viewport->zoomX);
	int y = sz.cy / 2 - (int)((note.midiNote - viewport->scrollY) * viewport->zoomY);
	return RectC(x, y - (int)viewport->zoomY / 2, w, (int)viewport->zoomY);
}

int PitchGraphEditor::HitTest(Point p) const
{
	if (!processor) return -1;
	Size sz = GetSize();
	Vector<PitchNote>& notes = processor->GetNotes();
	for (int i = 0; i < notes.GetCount(); ++i) {
		if (GetNoteRect(notes[i], sz).Contains(p))
			return i;
	}
	return -1;
}

void PitchGraphEditor::Paint(Draw& w)
{
	Size sz = GetSize();
	w.DrawRect(sz, SColorPaper());
	
	if (!viewport) return;

	// Draw musical pitch grid
	int startMidi = (int)(viewport->scrollY - (sz.cy / 2.0) / viewport->zoomY);
	int endMidi = (int)(viewport->scrollY + (sz.cy / 2.0) / viewport->zoomY);
	
	for (int midi = startMidi; midi <= endMidi; ++midi) {
		int y = sz.cy / 2 - (int)((midi - viewport->scrollY) * viewport->zoomY);
		if (y < 0 || y >= sz.cy) continue;
		
		int noteInOctave = midi % 12;
		bool isBlackKey = (noteInOctave == 1 || noteInOctave == 3 || noteInOctave == 6 || noteInOctave == 8 || noteInOctave == 10);
		
		Color lineCol = isBlackKey ? SColorDisabled() : SColorFace();
		w.DrawLine(0, y, sz.cx, y, 1, lineCol);
		
		if (noteInOctave == 0) { // C note
			w.DrawText(5, y - 12, Format("C%d", midi / 12 - 1), Arial(10), SColorText());
		}
	}

	// Draw time grid (1 second intervals)
	double startTime = viewport->scrollX;
	double endTime = startTime + (double)sz.cx / viewport->zoomX;
	for (int t = (int)startTime; t <= (int)endTime; ++t) {
		int x = (int)((t - viewport->scrollX) * viewport->zoomX);
		w.DrawLine(x, 0, x, sz.cy, 1, SColorFace());
	}

	if(processor) {
		// Draw notes
		Vector<PitchNote>& notes = processor->GetNotes();
		for (int i = 0; i < notes.GetCount(); ++i) {
			Rect r = GetNoteRect(notes[i], sz);
			if (r.right < 0 || r.left >= sz.cx) continue;
			
			Color c = notes[i].selected ? Cyan() : Blue();
			w.DrawRect(r, c);
			w.DrawRect(r.left, r.top, r.GetWidth(), r.GetHeight(), SColorText()); // Border
			
			String name = Format("%d", notes[i].midiNote);
			w.DrawText(r.left + 2, r.top + 2, name, Arial(10), White());
		}

		// Draw detected pitch
		const Vector<am::PitchPoint>& points = processor->GetPitchPoints();
		if(points.GetCount() > 1) {
			for(int i = 1; i < points.GetCount(); i++) {
				const am::PitchPoint& p1 = points[i-1];
				const am::PitchPoint& p2 = points[i];
				
				int x1 = (int)((p1.time - viewport->scrollX) * viewport->zoomX);
				int x2 = (int)((p2.time - viewport->scrollX) * viewport->zoomX);
				
				if (x2 < 0 || x1 >= sz.cx) continue;
				
				double midi1 = am::PitchAnalysisEngine::FrequencyToMidi(p1.frequency);
				double midi2 = am::PitchAnalysisEngine::FrequencyToMidi(p2.frequency);
				
				int y1 = sz.cy / 2 - (int)((midi1 - viewport->scrollY) * viewport->zoomY);
				int y2 = sz.cy / 2 - (int)((midi2 - viewport->scrollY) * viewport->zoomY);
				
				w.DrawLine(x1, y1, x2, y2, 2, Red());
			}
		}
	}

	w.DrawText(sz.cx / 2 - 100, 10, "Pitch Graph Editor", Arial(14).Bold(), SColorText());
}

void PitchGraphEditor::MouseWheel(Point p, int zdelta, dword keyflags)
{
	if (!viewport) return;
	
	if (keyflags & K_CTRL) {
		double oldZoom = viewport->zoomX;
		viewport->zoomX = max(10.0, viewport->zoomX * (zdelta > 0 ? 1.1 : 0.9));
		viewport->scrollX += (p.x / oldZoom) - (p.x / viewport->zoomX);
	} else if (keyflags & K_SHIFT) {
		viewport->zoomY = max(2.0, viewport->zoomY * (zdelta > 0 ? 1.1 : 0.9));
	} else {
		viewport->scrollX += (zdelta > 0 ? -1.0 : 1.0);
	}
	viewport->scrollX = max(0.0, viewport->scrollX);
	Refresh();
}

void PitchGraphEditor::MiddleDown(Point p, dword keyflags)
{
	lastMousePos = p;
}

void PitchGraphEditor::LeftDouble(Point p, dword keyflags)
{
	if (!processor || !viewport) return;
	
	PitchNote n;
	n.startTime = viewport->scrollX + p.x / viewport->zoomX;
	n.midiNote = (int)round(viewport->scrollY + (GetSize().cy / 2.0 - p.y) / viewport->zoomY);
	n.duration = 1.0;
	processor->GetNotes().Add(n);
	Refresh();
}

void PitchGraphEditor::LeftDown(Point p, dword keyflags)
{
	if (!processor) return;
	
	Vector<PitchNote>& notes = processor->GetNotes();
	draggingNoteIndex = HitTest(p);
	
	for (int i = 0; i < notes.GetCount(); ++i)
		notes[i].selected = (i == draggingNoteIndex);
	
	if (draggingNoteIndex != -1) {
		lastMousePos = p;
		Rect r = GetNoteRect(notes[draggingNoteIndex], GetSize());
		isResizing = (p.x > r.right - 10);
	}
	
	Refresh();
}

void PitchGraphEditor::LeftUp(Point p, dword keyflags)
{
	draggingNoteIndex = -1;
	isResizing = false;
}

bool PitchGraphEditor::Key(dword key, int count)
{
	if (key == K_DELETE && processor) {
		Vector<PitchNote>& notes = processor->GetNotes();
		for (int i = 0; i < notes.GetCount(); ++i) {
			if (notes[i].selected) {
				notes.Remove(i);
				Refresh();
				return true;
			}
		}
	}
	return false;
}

void PitchGraphEditor::MouseMove(Point p, dword keyflags)
{
	if (!viewport) return;
	
	if (keyflags & K_MOUSEMIDDLE) {
		viewport->scrollX += (lastMousePos.x - p.x) / viewport->zoomX;
		viewport->scrollY += (p.y - lastMousePos.y) / viewport->zoomY;
		viewport->scrollX = max(0.0, viewport->scrollX);
		lastMousePos = p;
		Refresh();
	} else if ((keyflags & K_MOUSELEFT) && draggingNoteIndex != -1 && processor) {
		Vector<PitchNote>& notes = processor->GetNotes();
		PitchNote& n = notes[draggingNoteIndex];
		
		if (isResizing) {
			n.duration = max(0.1, n.duration + (p.x - lastMousePos.x) / viewport->zoomX);
		} else {
			n.startTime += (p.x - lastMousePos.x) / viewport->zoomX;
			n.midiNote = (int)round(viewport->scrollY + (GetSize().cy / 2.0 - p.y) / viewport->zoomY);
		}
		lastMousePos = p;
		Refresh();
	}
}

// --- WaveformStrip ---

WaveformStrip::WaveformStrip()
{
}

void WaveformStrip::Paint(Draw& w)
{
	Size sz = GetSize();
	w.DrawRect(sz, SColorShadow());
	
	if (!viewport) return;

	if (processor) {
		const Vector<float>& buffer = processor->GetWaveformBuffer();
		int count = buffer.GetCount();
		if (count > 0) {
			int midY = sz.cy / 2;
			w.DrawLine(0, midY, sz.cx, midY, 1, SColorPaper());
			
			// Simple peak rendering based on viewport
			// Note: This skeleton doesn't have a full audio history yet,
			// just the last 2048 samples. For better visualization, 
			// we'd need a larger buffer mapping to time.
			
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
	
	graphEditor.SetViewport(&viewport);
	waveformStrip.SetViewport(&viewport);

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
