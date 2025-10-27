#ifndef _TransportUI_TransportWindow_h_
#define _TransportUI_TransportWindow_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

class UsageMetersPane : public ParentCtrl {
public:
	typedef UsageMetersPane CLASSNAME;
	UsageMetersPane();

	void SetUsage(double asioLoad, double diskLoad, bool asioOverload, bool diskOverload);
	void Layout() override;

private:
	void InitLayout();
	ProgressIndicator asioMeter;
	ProgressIndicator diskMeter;
	Label asioLabel;
	Label diskLabel;
	Label asioOverloadLed;
	Label diskOverloadLed;
};

class RecordingModePane : public ParentCtrl {
public:
	typedef RecordingModePane CLASSNAME;
	RecordingModePane();

	void SetLinearModeOptions(const Vector<String>& options);
	void SetCycleModeOptions(const Vector<String>& options);
	void SetState(const String& linear, const String& cycle, bool autoQuantize);

private:
	DropList linearMode;
	DropList cycleMode;
	Option autoQuantize;
};

class LocatorPane : public ParentCtrl {
public:
	typedef LocatorPane CLASSNAME;
	LocatorPane();

	void SetCaption(const String& caption);
	void SetLocatorTime(const String& time);
	void SetRollOffset(const String& rollText);
	void SetPunchEnabled(bool enabled);

private:
	Button goToButton;
	Button punchButton;
	EditString timeField;
	EditString rollField;
	Label captionLabel;
};

class TimeDisplayPane : public ParentCtrl {
public:
	typedef TimeDisplayPane CLASSNAME;
	TimeDisplayPane();

	void SetPrimaryFormat(const String& format);
	void SetPrimaryTime(const String& value);
	void SetSecondaryTime(const String& value);
	void SetSliderPosition(int position, int total);

private:
	Button minusButton;
	Button plusButton;
	Button swapButton;
	Button formatButton;
	EditString primaryDisplay;
	EditString secondaryDisplay;
	SliderCtrl positionSlider;
};

class TransportButtonPane : public ParentCtrl {
public:
	typedef TransportButtonPane CLASSNAME;
	TransportButtonPane();

	void SetState(bool cycle, bool playing, bool recording);
	void Layout() override;

private:
	Array<Button> buttons;
};

class TempoSyncPane : public ParentCtrl {
public:
	typedef TempoSyncPane CLASSNAME;
	TempoSyncPane();

	void SetMetronome(bool click, bool precount);
	void SetTempoState(bool tempoTrack, const String& signature, const String& tempoValue);
	void SetSyncState(bool externalSync);

private:
	Button metronomeButton;
	Button precountButton;
	Option tempoTrackOption;
	EditString signatureField;
	EditString tempoField;
	Option externalSyncOption;
};

class MarkerQuickPane : public ParentCtrl {
public:
	typedef MarkerQuickPane CLASSNAME;
	MarkerQuickPane();

	void SetMarkerActive(int index, bool active);
	void SetMarkerCount(int count);
	void Layout() override;

private:
	Button markerListButton;
	Array<Button> markerButtons;
	int markerCount = 15;
};

class ActivityMetersPane : public ParentCtrl {
public:
	typedef ActivityMetersPane CLASSNAME;
	ActivityMetersPane();

	void SetMidiActivity(int inLevel, int outLevel);
	void SetAudioActivity(const Vector<int>& channels, const Vector<bool>& clipFlags);
	void Layout() override;

private:
	ProgressIndicator midiIn;
	ProgressIndicator midiOut;
	Array<ProgressIndicator> audioMeters;
	Array<Label> clipLeds;
};

class MasterOutputPane : public ParentCtrl {
public:
	typedef MasterOutputPane CLASSNAME;
	MasterOutputPane();

	void SetGain(double gain);
	void ShowExpanded(bool show);

private:
	SliderCtrl compactSlider;
	SliderCtrl expandedSlider;
	bool expanded = false;
};

class VirtualKeyboardPane : public ParentCtrl {
public:
	typedef VirtualKeyboardPane CLASSNAME;
	VirtualKeyboardPane();

	void ToggleMode();
	void SetVisibleMode(bool pianoGraphics);
	void Layout() override;

private:
	void BuildQwertyLayout();
	void BuildPianoLayout();
	WithDropChoice<EditString> octaveSelector;
	Array<Button> whiteKeys;
	Array<Button> blackKeys;
	SliderCtrl velocitySlider;
	SliderCtrl modWheelA;
	SliderCtrl modWheelB;
	bool pianoMode = false;
};

class TransportWindow : public TopWindow {
public:
	typedef TransportWindow CLASSNAME;
	TransportWindow();

	void SetAlwaysOnTop(bool topmost);
	void SetUsageMeters(double asioLoad, double diskLoad, bool asioOverload, bool diskOverload);
	void SetRecordingModes(const String& linear, const Vector<String>& linearOptions,
	                      const String& cycle, const Vector<String>& cycleOptions,
	                      bool autoQuantize);
	void SetLeftLocator(const String& time, const String& preRoll, bool punchIn);
	void SetRightLocator(const String& time, const String& postRoll, bool punchOut);
	void SetPrimaryTime(const String& primary, const String& format, const String& secondary);
	void SetSlider(int position, int total);
	void SetTransportState(bool cycle, bool playing, bool recording);
	void SetTempoState(bool tempoTrack, const String& signature, const String& tempoValue);
	void SetSyncState(bool externalSync);
	void SetMarkers(int count, const Vector<bool>& active);
	void SetMidiActivity(int inLevel, int outLevel);
	void SetAudioActivity(const Vector<int>& channels, const Vector<bool>& clipFlags);
	void SetMasterGain(double gain, bool expanded);
	void ToggleVirtualKeyboard(bool showPianoMode);
	void Layout() override;

private:
	void BuildLayout();
	Button closeLeft;
	Button closeRight;
	UsageMetersPane usageMeters;
	RecordingModePane recordingModes;
	LocatorPane leftLocator;
	LocatorPane rightLocator;
	TimeDisplayPane timeDisplay;
	TransportButtonPane transportButtons;
	TempoSyncPane tempoSync;
	MarkerQuickPane markerQuick;
	ActivityMetersPane activityMeters;
	MasterOutputPane masterOutput;
	VirtualKeyboardPane virtualKeyboard;
};

}

#endif
