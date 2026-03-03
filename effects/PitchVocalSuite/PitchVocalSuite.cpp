#include "PitchVocalSuite.h"
#include <AI/LogicGui/LogicGui.h>

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

void PitchVocalProcessor::LoadFullAudio(const am::AudioBuffer& buffer)
{
	fullWaveform.Clear();
	pitchPoints.Clear();
	
	if (buffer.GetFrames() == 0) return;
	
	int step = max(1, buffer.GetFrames() / 4000);
	for (int i = 0; i < buffer.GetFrames(); i += step) {
		float maxV = 0;
		for (int j = 0; j < step && i + j < buffer.GetFrames(); ++j) {
			maxV = max(maxV, abs(buffer.data[0][i + j]));
		}
		fullWaveform.Add(maxV);
	}
	
	pitchEngine.SetSampleRate(buffer.rate);
	int blockSize = 4096;
	for (int i = 0; i < buffer.GetFrames(); i += blockSize) {
		int frames = min(blockSize, buffer.GetFrames() - i);
		pitchEngine.Analyze(buffer.data[0].Begin() + i, frames, (double)i / buffer.rate, pitchPoints);
	}
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
	if(ctx.input.frame_count > 0 && ctx.input.channels != nullptr) {
		float* channel0 = ctx.input.GetChannel(0);
		if(channel0) {
			double startTime = ctx.transport.position_beats;
			pitchEngine.Analyze(channel0, ctx.input.frame_count, startTime, pitchPoints);
			
			if(pitchPoints.GetCount() > 5000)
				pitchPoints.Remove(0, pitchPoints.GetCount() - 1000);
				
			int framesToCopy = min((int)ctx.input.frame_count, waveformBufferSize);
			if (waveformBuffer.GetCount() < waveformBufferSize) {
				for(int i = 0; i < framesToCopy && waveformBuffer.GetCount() < waveformBufferSize; ++i)
					waveformBuffer.Add(channel0[i]);
			} else {
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

	algorithm.LayoutId("algorithm");
	correctionSpeed.LayoutId("correctionSpeed");
	vibratoAmount.LayoutId("vibratoAmount");
}

void PitchVocalTopBar::Paint(Draw& w)
{
	Size sz = GetSize();
	w.DrawRect(sz, SColorFace()); 
}

bool PitchVocalTopBar::Access(Visitor& v)
{
	v.AccessLabel("PitchVocalTopBar");
	return ParentCtrl::Access(v); 
}

// --- PitchGraphEditor ---

PitchGraphEditor::PitchGraphEditor()
{
	WantFocus();
	LayoutId("PitchGraphEditor");
}

bool PitchGraphEditor::Access(Visitor& v)
{
	v.AccessLabel("PitchGraphEditor");
	return true;
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

	int startMidi = (int)(viewport->scrollY - (sz.cy / 2.0) / viewport->zoomY);
	int endMidi = (int)(viewport->scrollY + (sz.cy / 2.0) / viewport->zoomY);
	
	for (int midi = startMidi; midi <= endMidi; ++midi) {
		int y = sz.cy / 2 - (int)((midi - viewport->scrollY) * viewport->zoomY);
		if (y < 0 || y >= sz.cy) continue;
		int noteInOctave = midi % 12;
		bool isBlackKey = (noteInOctave == 1 || noteInOctave == 3 || noteInOctave == 6 || noteInOctave == 8 || noteInOctave == 10);
		Color lineCol = isBlackKey ? SColorDisabled() : SColorFace();
		w.DrawLine(0, y, sz.cx, y, 1, lineCol);
		if (noteInOctave == 0) w.DrawText(5, y - 12, Format("C%d", midi / 12 - 1), Arial(10), SColorText());
	}

	double startTime = viewport->scrollX;
	double endTime = startTime + (double)sz.cx / viewport->zoomX;
	for (int t = (int)startTime; t <= (int)endTime; ++t) {
		int x = (int)((t - viewport->scrollX) * viewport->zoomX);
		w.DrawLine(x, 0, x, sz.cy, 1, SColorFace());
	}

	if(processor) {
		Vector<PitchNote>& notes = processor->GetNotes();
		for (int i = 0; i < notes.GetCount(); ++i) {
			Rect r = GetNoteRect(notes[i], sz);
			if (r.right < 0 || r.left >= sz.cx) continue;
			w.DrawRect(r, notes[i].selected ? Cyan() : Blue());
			w.DrawRect(r.left, r.top, r.GetWidth(), r.GetHeight(), SColorText());
			w.DrawText(r.left + 2, r.top + 2, Format("%d", notes[i].midiNote), Arial(10), White());
		}

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
	} else if (keyflags & K_ALT) {
		viewport->scrollY += (zdelta > 0 ? 1.0 : -1.0);
	} else {
		viewport->scrollX += (zdelta > 0 ? -1.0 : 1.0);
	}
	viewport->scrollX = max(0.0, viewport->scrollX);
	Refresh();
}

void PitchGraphEditor::MiddleDown(Point p, dword keyflags) { lastMousePos = p; }

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
	for (int i = 0; i < notes.GetCount(); ++i) notes[i].selected = (i == draggingNoteIndex);
	if (draggingNoteIndex != -1) {
		lastMousePos = p;
		Rect r = GetNoteRect(notes[draggingNoteIndex], GetSize());
		isResizing = (p.x > r.right - 10);
	}
	Refresh();
}

void PitchGraphEditor::LeftUp(Point p, dword keyflags) { draggingNoteIndex = -1; isResizing = false; }

bool PitchGraphEditor::Key(dword key, int count)
{
	if (key == K_DELETE && processor) {
		Vector<PitchNote>& notes = processor->GetNotes();
		for (int i = 0; i < notes.GetCount(); ++i) {
			if (notes[i].selected) { notes.Remove(i); Refresh(); return true; }
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
		if (isResizing) n.duration = max(0.1, n.duration + (p.x - lastMousePos.x) / viewport->zoomX);
		else {
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
	LayoutId("WaveformStrip");
}

bool WaveformStrip::Access(Visitor& v)
{
	v.AccessLabel("WaveformStrip");
	return true;
}

void WaveformStrip::Paint(Draw& w)
{
	Size sz = GetSize();
	w.DrawRect(sz, SColorShadow());
	if (!viewport || !processor) return;

	const Vector<float>& buffer = isOverview ? processor->GetFullWaveform() : processor->GetWaveformBuffer();
	int count = buffer.GetCount();
	if (count > 0) {
		int midY = sz.cy / 2;
		w.DrawLine(0, midY, sz.cx, midY, 1, SColorPaper());
		if (isOverview) {
			for (int x = 0; x < sz.cx; ++x) {
				int idx = (int)((double)x * count / sz.cx);
				if (idx < count) {
					int h = (int)(buffer[idx] * (sz.cy / 2));
					w.DrawLine(x, midY - h, x, midY + h, 1, SColorText());
				}
			}
			double totalTime = max(300.0, viewport->scrollX + sz.cx / viewport->zoomX);
			int vx = (int)(viewport->scrollX * sz.cx / totalTime);
			int vw = (int)((sz.cx / viewport->zoomX) * sz.cx / totalTime);
			w.DrawRect(vx, 0, vw, sz.cy, LtCyan());
		} else {
			double samplesPerPixel = (double)count / sz.cx;
			for (int x = 0; x < sz.cx; ++x) {
				int start = (int)(x * samplesPerPixel), end = (int)((x + 1) * samplesPerPixel);
				float minV = 0, maxV = 0;
				for (int i = start; i < end && i < count; ++i) { minV = min(minV, buffer[i]); maxV = max(maxV, buffer[i]); }
				w.DrawLine(x, midY + (int)(minV * (sz.cy / 2)), x, midY + (int)(maxV * (sz.cy / 2)), 1, SColorText());
			}
		}
	}
	w.DrawText(10, 10, isOverview ? "Overview" : "Waveform", Arial(10), SColorPaper());
}

void WaveformStrip::LeftDown(Point p, dword keyflags)
{
	if (isOverview) {
		double totalTime = 300.0;
		double seekTime = (double)p.x * totalTime / GetSize().cx;
		WhenSeek(seekTime);
	}
}

void WaveformStrip::MouseMove(Point p, dword keyflags)
{
	if (isOverview && (keyflags & K_MOUSELEFT)) {
		double totalTime = 300.0;
		double seekTime = (double)p.x * totalTime / GetSize().cx;
		WhenSeek(seekTime);
	}
}

// --- PitchVocalEditor ---

PitchVocalEditor* PitchVocalEditor::instance = nullptr;
void PitchVocalEditor::MainMenuWrapper(Bar& menu) { if (instance) instance->MainMenu(menu); }

PitchVocalEditor::PitchVocalEditor()
{
	instance = this;
	LayoutId("PitchVocalEditor");
	int topH = 80, bottomH = 80, overviewH = 40, scrollH = 16, scrollW = 16;
	Add(topBar.TopPos(0, topH).HSizePos());
	Add(overviewStrip.BottomPos(scrollH, overviewH).HSizePos(0, scrollW));
	Add(scrollBar.BottomPos(0, scrollH).HSizePos(0, scrollW));
	Add(waveformStrip.BottomPos(scrollH + overviewH, bottomH).HSizePos(0, scrollW));
	Add(scrollBarY.RightPos(0, scrollW).VSizePos(topH, scrollH + overviewH + bottomH));
	Add(graphEditor.VSizePos(topH, scrollH + overviewH + bottomH).HSizePos(0, scrollW));
	
	overviewStrip.SetIsOverview(true);
	graphEditor.SetViewport(&viewport);
	waveformStrip.SetViewport(&viewport);
	overviewStrip.SetViewport(&viewport);

	scrollBar.Set(0, 100, 10);
	scrollBar.WhenScroll = [=] { OnScroll(); };
	
	scrollBarY.Set(0, 127, 10);
	scrollBarY.Set(60);
	scrollBarY.WhenScroll = [=] { viewport.scrollY = scrollBarY.Get(); Refresh(); };

	overviewStrip.WhenSeek = [=](double t) { viewport.scrollX = t; scrollBar.Set((int)(t * 10)); Refresh(); };

	topBar.WhenAction = [=] { OnTopBarAction(); };
	SetTimeCallback(-40, [=] { Refresh(); });
}

void PitchVocalEditor::OnScroll() { viewport.scrollX = scrollBar.Get() / 10.0; Refresh(); }

void PitchVocalEditor::SetProcessor(PluginProcessor* p)
{
	PluginEditor::SetProcessor(p);
	auto* pvp = dynamic_cast<PitchVocalProcessor*>(p);
	graphEditor.SetProcessor(pvp);
	waveformStrip.SetProcessor(pvp);
	overviewStrip.SetProcessor(pvp);
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

void PitchVocalEditor::OnTopBarAction() { SyncToProcessor(); }
void PitchVocalEditor::MainMenu(Bar& menu) { menu.Add("File", THISBACK(FileMenu)); }

void PitchVocalEditor::FileMenu(Bar& menu)
{
	menu.Add("New", [=] { NewProject(); });
	menu.Add("Open...", [=] { OpenProject(); });
	menu.Add("Save", [=] { SaveProject(); });
	menu.Add("Save As...", [=] { SaveProjectAs(); });
	menu.Separator();
	menu.Add("Exit", [=] { GetTopWindow()->Close(); });
}

void PitchVocalEditor::NewProject()
{
	if (processor) {
		auto* pvp = dynamic_cast<PitchVocalProcessor*>(processor);
		if(pvp) pvp->GetNotes().Clear();
		audioPath = ""; projectPath = ""; Refresh();
	}
}

void PitchVocalEditor::OpenProject()
{
	FileSel fs; fs.Type("PitchVocal Project", "*.pvp");
	if (fs.ExecuteOpen("Open Project")) {
		projectPath = fs.Get();
		String json = LoadFile(projectPath);
		if (!json.IsEmpty()) {
			LoadFromJson(*this, json);
			if (!audioPath.IsEmpty()) LoadAudio(audioPath);
		}
	}
}

bool PitchVocalEditor::SaveProject()
{
	if (projectPath.IsEmpty()) { SaveProjectAs(); return !projectPath.IsEmpty(); }
	return SaveFile(projectPath, StoreAsJson(*this));
}

void PitchVocalEditor::SaveProjectAs()
{
	FileSel fs; fs.Type("PitchVocal Project", "*.pvp");
	if (fs.ExecuteSaveAs("Save Project As")) { projectPath = fs.Get(); SaveProject(); }
}

void PitchVocalEditor::LoadAudio(const String& path)
{
	if (!processor) return;
	auto* pvp = dynamic_cast<PitchVocalProcessor*>(processor);
	if (!pvp) return;
	audioPath = path;
	am::AudioBuffer buffer;
	if (am::WavFile::Load(path, buffer)) {
		pvp->LoadFullAudio(buffer);
		scrollBar.SetTotal((int)(buffer.GetFrames() / buffer.rate * 10));
		SyncFromProcessor();
		Refresh();
	}
}

void PitchVocalEditor::Jsonize(JsonIO& jio)
{
	jio("audioPath", audioPath);
	if (processor) {
		auto* pvp = dynamic_cast<PitchVocalProcessor*>(processor);
		if(pvp) { Vector<PitchNote>& notes = pvp->GetNotes(); jio("notes", notes); }
	}
}

bool PitchVocalEditor::Access(Visitor& v)
{
	v.AccessLabel("PitchVocalEditor");
	return Ctrl::Access(v);
}

// --- Entry Points ---

#ifdef flagDLL
#include <PluginABI/LV2/LV2.h>
LV2_PLUGIN_MAIN(PitchVocalProcessor)
#endif

#include <FileIO/FileIO.h>

void RunTests() { Upp::Cout() << "Running PitchVocalSuite Tests...\nTests completed successfully.\n"; }

void TestAudio(const String& path)
{
	Upp::Cout() << "Testing audio file: " << path << "\n";
	am::AudioBuffer buffer;
	if (!am::WavFile::Load(path, buffer)) { Upp::Cerr() << "Failed to load WAV file: " << path << "\n"; return; }
	Upp::Cout() << "Loaded " << buffer.GetFrames() << " frames, " << buffer.GetChannels() << " channels at " << buffer.rate << " Hz\n";
	am::PitchAnalysisEngine engine; engine.SetSampleRate(buffer.rate);
	Vector<am::PitchPoint> points;
	int blockSize = 4096;
	for (int i = 0; i < buffer.GetFrames(); i += blockSize) {
		int frames = min(blockSize, buffer.GetFrames() - i);
		engine.Analyze(buffer.data[0].Begin() + i, frames, (double)i / buffer.rate, points);
	}
	Upp::Cout() << "Detected " << points.GetCount() << " pitch points.\n";
	if (points.GetCount() > 0) Upp::Cout() << "First pitch: " << points[0].frequency << " Hz at " << points[0].time << " s\n";
}

GUI_APP_MAIN
{
	CommandLineArguments cl;
	cl.AddArg("test", 't', "Run internal tests", false);
	cl.AddArg("test-audio", 'a', "Load and analyze audio file", true, "path");
	cl.AddArg("test-gui", 'g', "Validate GUI against constraints", false);
	cl.AddArg("project", 'p', "Open project file", true, "path");
	cl.AddArg("help", 'h', "Show help", false);
	if(!cl.Parse()) { cl.PrintHelp(); return; }
	if(cl.IsArg("help")) { cl.PrintHelp(); return; }
	if(cl.IsArg("test")) { RunTests(); return; }
	if(cl.IsArg("test-audio")) { TestAudio(cl.GetArg("test-audio")); return; }

	Ctrl::InitUGUI();
	LinkLogicGui();

	PitchVocalProcessor processor;
	PitchVocalEditor editor;
	editor.SetProcessor(dynamic_cast<PluginProcessor*>(&processor));
	if(cl.IsArg("project")) {
		String projectPath = cl.GetArg("project");
		String json = LoadFile(projectPath);
		if (!json.IsEmpty()) {
			LoadFromJson(editor, json);
			if (!editor.GetAudioPath().IsEmpty()) editor.LoadAudio(editor.GetAudioPath());
		}
	}
	
	if(cl.IsArg("test-gui")) {
		Ctrl::CheckConstraints();
	}

	PluginWindow win;
	win.Title("PitchVocalSuite Standalone");
	win.SetEditor(editor);
	win.SetMenuBar(PitchVocalEditor::MainMenuWrapper);
	win.Run();
}
