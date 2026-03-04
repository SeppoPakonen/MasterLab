#ifndef _PitchVocalSuite_PitchVocalSuite_h_
#define _PitchVocalSuite_PitchVocalSuite_h_

#include <Core/Core.h>
#include <Draw/Draw.h>
#include <AudioAnalysis/PitchAnalysis.h>
#include <PluginSDK/PluginSDK.h>

#ifdef GUI
#include <CtrlLib/CtrlLib.h>
#include <AudioUI/AudioUI.h>
#include <CtrlLog/CtrlLog.h>
#endif

using namespace Upp;
using namespace PluginSDK;

struct PitchVocalViewport {
	double zoomX = 100.0;
	double scrollX = 0.0;
	double zoomY = 20.0;
	double scrollY = 60.0;
};

struct PitchNote : public Moveable<PitchNote> {
	double startTime;
	double duration;
	int midiNote;
	bool selected = false;
	
	PitchNote() : startTime(0), duration(1.0), midiNote(60) {}
	
	void Jsonize(JsonIO& jio) {
		jio("startTime", startTime)("duration", duration)("midiNote", midiNote);
	}
};

// DSP Processor for PitchVocalSuite
class PitchVocalProcessor : public PluginProcessor {
public:
	PitchVocalProcessor();
	virtual void Process(ProcessContext& ctx) override;

	virtual Upp::String GetURI() const override;
	virtual Upp::String GetName() const override;

	const Vector<am::PitchPoint>& GetPitchPoints() const { return pitchPoints; }
	const Vector<float>& GetWaveformBuffer() const { return waveformBuffer; }
	const Vector<float>& GetFullWaveform() const { return fullWaveform; }
	Vector<PitchNote>& GetNotes() { return notes; }
	
	void LoadFullAudio(const am::AudioBuffer& buffer, const String& path);
	String GetCachePath(const String& path);

	Event<String> WhenLog;

public:
	void Log(const String& s) { WhenLog(s); }

	am::PitchAnalysisEngine pitchEngine;
	Vector<am::PitchPoint> pitchPoints;
	Vector<float> waveformBuffer;
	Vector<float> fullWaveform;
	Vector<PitchNote> notes;
	
	am::AudioBuffer fullAudioBuffer;
	int waveformBufferSize = 2048;
};

#ifdef GUI

// Custom control for pitch graph editing
class PitchGraphEditor : public Ctrl {
public:
	typedef PitchGraphEditor CLASSNAME;
	PitchGraphEditor();

	void SetProcessor(PitchVocalProcessor* p) { processor = p; }
	void SetViewport(PitchVocalViewport* v) { viewport = v; }
	virtual void Paint(Draw& w) override;
	virtual void MouseWheel(Point p, int zdelta, dword keyflags) override;
	virtual void MiddleDown(Point p, dword keyflags) override;
	virtual void MouseMove(Point p, dword keyflags) override;
	virtual void LeftDouble(Point p, dword keyflags) override;
	virtual void LeftDown(Point p, dword keyflags) override;
	virtual void LeftUp(Point p, dword keyflags) override;
	virtual bool Key(dword key, int count) override;
	virtual bool Access(Visitor& v) override;

private:
	Rect GetNoteRect(const PitchNote& note, const Size& sz) const;
	int HitTest(Point p) const;

	PitchVocalProcessor* processor = nullptr;
	PitchVocalViewport* viewport = nullptr;
	Point lastMousePos;
	int draggingNoteIndex = -1;
	bool isResizing = false;
};

// Custom control for waveform visualization
class WaveformStrip : public Ctrl {
public:
	typedef WaveformStrip CLASSNAME;
	WaveformStrip();

	void SetProcessor(PitchVocalProcessor* p) { processor = p; }
	void SetViewport(PitchVocalViewport* v) { viewport = v; }
	void SetIsOverview(bool b) { isOverview = b; }
	virtual void Paint(Draw& w) override;
	virtual void LeftDown(Point p, dword keyflags) override;
	virtual void MouseMove(Point p, dword keyflags) override;
	virtual bool Access(Visitor& v) override;

	Event<double> WhenSeek;

private:
	PitchVocalProcessor* processor = nullptr;
	PitchVocalViewport* viewport = nullptr;
	bool isOverview = false;
};

// Top bar for global controls
class PitchVocalTopBar : public ParentCtrl {
public:
	typedef PitchVocalTopBar CLASSNAME;
	PitchVocalTopBar();

	virtual void Paint(Draw& w) override;
	virtual bool Access(Visitor& v) override;

	Event<> WhenAction;

	int GetAlgorithm() const { return algorithm.GetIndex(); }
	void SetAlgorithm(int i) { algorithm.SetIndex(i); }

	double GetSpeed() const { return correctionSpeed.GetData(); }
	void SetSpeed(double v) { correctionSpeed.SetData(v); }

	double GetVibrato() const { return vibratoAmount.GetData(); }
	void SetVibrato(double v) { vibratoAmount.SetData(v); }

private:
	DropList algorithm;
	SliderCtrl correctionSpeed;
	SliderCtrl vibratoAmount;
	
	Label lblAlgorithm;
	Label lblSpeed;
	Label lblVibrato;
};

// Main editor container
class PitchVocalEditor : public PluginEditor {
public:
	typedef PitchVocalEditor CLASSNAME;
	PitchVocalEditor();

	virtual void SetProcessor(PluginProcessor* p) override;
	virtual void SyncToProcessor() override;
	virtual void SyncFromProcessor() override;

	void MainMenu(Bar& menu);
	void FileMenu(Bar& menu);

	static void MainMenuWrapper(Bar& menu);
	static PitchVocalEditor* instance;
	
	void LoadAudio(const String& path);
	virtual void Jsonize(JsonIO& jio) override;
	virtual bool Access(Visitor& v) override;

	String GetAudioPath() const { return audioPath; }

private:
	void OnTopBarAction();
	void OnScroll();
	
	// File operations
	void NewProject();
	void OpenProject();
	bool SaveProject();
	void SaveProjectAs();

	PitchVocalTopBar topBar;
	PitchGraphEditor graphEditor;
	WaveformStrip waveformStrip;
	WaveformStrip overviewStrip;
	ScrollBar scrollBar;
	ScrollBar scrollBarY;
	PitchVocalViewport viewport;
	
	StaticRect editorArea;
	One<CtrlLog> ctrlLog;
	Splitter logSplitter;
	
	String projectPath;
	String audioPath;
};

#endif // GUI

#endif
