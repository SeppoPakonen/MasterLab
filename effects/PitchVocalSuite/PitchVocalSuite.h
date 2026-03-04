#ifndef _PitchVocalSuite_PitchVocalSuite_h_
#define _PitchVocalSuite_PitchVocalSuite_h_

#include <CtrlLib/CtrlLib.h>
#include <PitchVocalSuiteCore/PitchVocalSuiteCore.h>
#include <AudioUI/AudioUI.h>
#include <CtrlLog/CtrlLog.h>
#include <SoftAudio/SoftAudio.h>

using namespace Upp;

// Viewport for scrolling/zooming editor
struct EditorViewport {
	double scrollX = 0, scrollY = 60;
	double zoomX = 50, zoomY = 10;
};

class PitchVocalTopBar : public Ctrl {
public:
	typedef PitchVocalTopBar CLASSNAME;
	PitchVocalTopBar();
	
	int GetAlgorithm() const { return algorithm.GetIndex(); }
	void SetAlgorithm(int i) { algorithm.SetIndex(i); }
	double GetSpeed() const { return correctionSpeed.GetData(); }
	void SetSpeed(double d) { correctionSpeed.SetData(d); }
	double GetVibrato() const { return vibratoAmount.GetData(); }
	void SetVibrato(double d) { vibratoAmount.SetData(d); }
	double GetPitchShift() const { return pitchShift.GetData(); }
	void SetPitchShift(double d) { pitchShift.SetData(d); }
	
	Event<> WhenAction;

protected:
	virtual void Paint(Draw& w) override;
	virtual bool Access(Visitor& v) override;

private:
	Label lblAlgorithm, lblSpeed, lblVibrato, lblPitchShift;
	DropList algorithm;
	SliderCtrl correctionSpeed, vibratoAmount, pitchShift;
};

class PitchGraphEditor : public Ctrl {
public:
	typedef PitchGraphEditor CLASSNAME;
	PitchGraphEditor();
	
	void SetProcessor(PitchVocalProcessor* p) { processor = p; }
	void SetViewport(EditorViewport* v) { viewport = v; }
	
protected:
	virtual void Paint(Draw& w) override;
	virtual void MouseWheel(Point p, int zdelta, dword keyflags) override;
	virtual void MiddleDown(Point p, dword keyflags) override;
	virtual void LeftDouble(Point p, dword keyflags) override;
	virtual void LeftDown(Point p, dword keyflags) override;
	virtual void LeftUp(Point p, dword keyflags) override;
	virtual bool Key(dword key, int count) override;
	virtual void MouseMove(Point p, dword keyflags) override;
	
private:
	Rect GetNoteRect(const PitchNote& note, const Size& sz) const;
	int HitTest(Point p) const;
	
	PitchVocalProcessor* processor = nullptr;
	EditorViewport* viewport = nullptr;
	Point lastMousePos;
	int draggingNoteIndex = -1;
	bool isResizing = false;
};

class WaveformStrip : public Ctrl {
public:
	typedef WaveformStrip CLASSNAME;
	WaveformStrip();
	
	void SetProcessor(PitchVocalProcessor* p) { processor = p; }
	void SetViewport(EditorViewport* v) { viewport = v; }
	void SetIsOverview(bool b) { isOverview = b; }
	
	Event<double> WhenSeek;

protected:
	virtual void Paint(Draw& w) override;
	virtual void LeftDown(Point p, dword keyflags) override;
	virtual void MouseMove(Point p, dword keyflags) override;
	virtual bool Access(Visitor& v) override;
	
private:
	PitchVocalProcessor* processor = nullptr;
	EditorViewport* viewport = nullptr;
	bool isOverview = false;
};

class PitchVocalEditor : public PluginSDK::PluginEditor {
public:
	typedef PitchVocalEditor CLASSNAME;
	PitchVocalEditor();
	
	virtual void SetProcessor(PluginSDK::PluginProcessor* p) override;
	virtual void SyncToProcessor() override;
	virtual void SyncFromProcessor() override;

	void MainMenu(Bar& menu);
	static void MainMenuWrapper(Bar& menu);
	
	void LoadAudio(const String& path);
	String GetAudioPath() const { return audioPath; }
	
	void Jsonize(JsonIO& jio);
	
protected:
	virtual bool Access(Visitor& v) override;

private:
	void FileMenu(Bar& menu);
	void NewProject();
	void OpenProject();
	bool SaveProject();
	void SaveProjectAs();
	void OnScroll();
	void OnTopBarAction();

	PitchVocalTopBar topBar;
	WaveformStrip waveformStrip, overviewStrip;
	PitchGraphEditor graphEditor;
	ScrollBar scrollBar, scrollBarY;
	Splitter logSplitter, editorArea;
	CtrlLog* ctrlLog;
	
	EditorViewport viewport;
	String projectPath, audioPath;
	static PitchVocalEditor* instance;
};

#endif
