#include "TransportUI.h"

namespace am {

UsageMetersPane::UsageMetersPane() {
	InitLayout();
}

void UsageMetersPane::InitLayout() {
	SetFrame(ThinInsetFrame());
	asioLabel.SetText("ASIO");
	diskLabel.SetText("Disk");
	asioOverloadLed.SetText(" ");
	diskOverloadLed.SetText(" ");
	asioOverloadLed.Ink(SLtRed);
	diskOverloadLed.Ink(SLtRed);
	asioOverloadLed.Hide();
	diskOverloadLed.Hide();
	asioMeter.Vertical();
	diskMeter.Vertical();
	asioMeter.SetLimits(0, 100);
	diskMeter.SetLimits(0, 100);
	Add(asioLabel);
	Add(diskLabel);
	Add(asioOverloadLed);
	Add(diskOverloadLed);
	Add(asioMeter);
	Add(diskMeter);
}

void UsageMetersPane::Layout() {
	Size sz = GetSize();
	int meterWidth = 28;
	asioLabel.SetRect(0, 0, meterWidth, 16);
	diskLabel.SetRect(meterWidth, 0, meterWidth, 16);
	asioOverloadLed.SetRect(4, 18, meterWidth - 8, 8);
	diskOverloadLed.SetRect(meterWidth + 4, 18, meterWidth - 8, 8);
	asioMeter.SetRect(8, 30, meterWidth - 16, sz.cy - 34);
	diskMeter.SetRect(meterWidth + 8, 30, meterWidth - 16, sz.cy - 34);
}

void UsageMetersPane::SetUsage(double asioLoad, double diskLoad, bool asioOverload, bool diskOverload) {
	asioMeter.Set((int)(asioLoad * 100.0));
	diskMeter.Set((int)(diskLoad * 100.0));
	asioOverloadLed.Show(asioOverload);
	diskOverloadLed.Show(diskOverload);
}

RecordingModePane::RecordingModePane() {
	SetFrame(ThinInsetFrame());
	linearMode.Add("Normal");
	linearMode.Add("Merge");
	linearMode.Add("Replace");
	cycleMode.Add("Mix MIDI");
	cycleMode.Add("Overwrite MIDI");
	cycleMode.Add("Keep Last");
	cycleMode.Add("Stacked 2 (no mute)");
	autoQuantize.SetLabel("Auto Quantize");
	Add(linearMode.TopPos(4, 22).HSizePos(4, 4));
	Add(cycleMode.TopPos(30, 22).HSizePos(4, 4));
	Add(autoQuantize.TopPos(56, 22).HSizePos(4, 4));
}

void RecordingModePane::SetLinearModeOptions(const Vector<String>& options) {
	linearMode.Clear();
	for(const String& opt : options)
		linearMode.Add(opt);
}

void RecordingModePane::SetCycleModeOptions(const Vector<String>& options) {
	cycleMode.Clear();
	for(const String& opt : options)
		cycleMode.Add(opt);
}

void RecordingModePane::SetState(const String& linear, const String& cycle, bool autoQuantizeOn) {
	linearMode.SetData(linear);
	cycleMode.SetData(cycle);
	autoQuantize.Set(autoQuantizeOn);
}

LocatorPane::LocatorPane() {
	SetFrame(ThinInsetFrame());
	captionLabel.SetText("Locator");
	goToButton.SetLabel("Go");
	punchButton.SetLabel("Punch");
	timeField.SetText("1.1.1.0");
	rollField.SetText("0.0.1.0");
	Add(captionLabel.TopPos(0, 18).HSizePos(4, 4));
	Add(goToButton.TopPos(20, 22).LeftPos(4, 40));
	Add(punchButton.TopPos(20, 22).RightPos(4, 60));
	Add(timeField.TopPos(46, 22).HSizePos(4, 4));
	Add(rollField.TopPos(72, 22).HSizePos(4, 4));
}

void LocatorPane::SetCaption(const String& caption) {
	captionLabel.SetText(caption);
}

void LocatorPane::SetLocatorTime(const String& time) {
	timeField.SetText(time);
}

void LocatorPane::SetRollOffset(const String& rollText) {
	rollField.SetText(rollText);
}

void LocatorPane::SetPunchEnabled(bool enabled) {
	punchButton.SetImage(enabled ? CtrlImg::Record() : Null);
}

TimeDisplayPane::TimeDisplayPane() {
	minusButton.SetLabel("-");
	plusButton.SetLabel("+");
	swapButton.SetLabel("Swap");
	formatButton.SetLabel("Format");
	primaryDisplay.SetText("1.01.00.000");
	secondaryDisplay.SetText("00:00:00.000");
	positionSlider.SetLimits(0, 1000);
	Add(minusButton.TopPos(0, 22).LeftPos(0, 40));
	Add(plusButton.TopPos(0, 22).LeftPos(44, 40));
	Add(formatButton.TopPos(0, 22).LeftPos(88, 80));
	Add(swapButton.TopPos(0, 22).LeftPos(172, 80));
	Add(primaryDisplay.TopPos(26, 24).HSizePos(0, 0));
	Add(secondaryDisplay.TopPos(54, 24).HSizePos(0, 0));
	Add(positionSlider.BottomPos(0, 20).HSizePos(0, 0));
}

void TimeDisplayPane::SetPrimaryFormat(const String& format) {
	formatButton.SetLabel(format);
}

void TimeDisplayPane::SetPrimaryTime(const String& value) {
	primaryDisplay.SetText(value);
}

void TimeDisplayPane::SetSecondaryTime(const String& value) {
	secondaryDisplay.SetText(value);
}

void TimeDisplayPane::SetSliderPosition(int position, int total) {
	positionSlider.SetLimits(0, max(total, 1));
	positionSlider <<= min(max(position, 0), max(total, 1));
}

TransportButtonPane::TransportButtonPane() {
	static const char* labels[] = {
		"|<", "<<", ">>", ">|", "Cycle", "Stop", "Play", "Record"
	};
	for(const char* txt : labels) {
		Button& b = buttons.Create<Button>();
		b.SetLabel(txt);
		Add(b);
	}
}

void TransportButtonPane::Layout() {
	Size sz = GetSize();
	int count = buttons.GetCount();
	int width = count ? sz.cx / count : sz.cx;
	for(int i = 0; i < count; ++i)
		buttons[i].SetRect(i * width, 0, width, sz.cy);
}

void TransportButtonPane::SetState(bool cycle, bool playing, bool recording) {
	if(buttons.GetCount() >= 8) {
		buttons[4].Set(cycle);
		buttons[6].SetImage(playing ? CtrlImg::Play() : Null);
		buttons[7].SetImage(recording ? CtrlImg::Record() : Null);
	}
}

TempoSyncPane::TempoSyncPane() {
	SetFrame(ThinInsetFrame());
	metronomeButton.SetLabel("Click");
	precountButton.SetLabel("Precount");
	tempoTrackOption.SetLabel("Tempo Track");
	signatureField.SetText("4/4");
	tempoField.SetText("120.00");
	externalSyncOption.SetLabel("External Sync");
	Add(metronomeButton.TopPos(0, 22).HSizePos(4, 4));
	Add(precountButton.TopPos(26, 22).HSizePos(4, 4));
	Add(tempoTrackOption.TopPos(52, 20).HSizePos(4, 4));
	Add(signatureField.TopPos(74, 20).HSizePos(4, 4));
	Add(tempoField.TopPos(96, 20).HSizePos(4, 4));
	Add(externalSyncOption.BottomPos(4, 20).HSizePos(4, 4));
}

void TempoSyncPane::SetMetronome(bool click, bool precount) {
	metronomeButton <<= click;
	precountButton <<= precount;
}

void TempoSyncPane::SetTempoState(bool tempoTrack, const String& signature, const String& tempoValue) {
	tempoTrackOption.Set(tempoTrack);
	signatureField.SetText(signature);
	tempoField.SetText(tempoValue);
}

void TempoSyncPane::SetSyncState(bool externalSync) {
	externalSyncOption.Set(externalSync);
}

MarkerQuickPane::MarkerQuickPane() {
	markerListButton.SetLabel("Markers");
	Add(markerListButton);
	SetMarkerCount(markerCount);
}

void MarkerQuickPane::Layout() {
	Size sz = GetSize();
	markerListButton.SetRect(0, 0, sz.cx, 24);
	int rows = 3;
	int buttons = markerButtons.GetCount();
	int cols = rows ? (buttons + rows - 1) / rows : 0;
	int cellW = cols ? sz.cx / cols : sz.cx;
	int cellH = rows ? (sz.cy - 24) / rows : sz.cy;
	for(int i = 0; i < buttons; ++i) {
		int row = i % rows;
		int col = i / rows;
		markerButtons[i].SetRect(col * cellW, 24 + row * cellH, cellW, cellH);
	}
}

void MarkerQuickPane::SetMarkerActive(int index, bool active) {
	if(index >= 0 && index < markerButtons.GetCount())
		markerButtons[index].SetCheck(active);
}

void MarkerQuickPane::SetMarkerCount(int count) {
	for(int i = markerButtons.GetCount() - 1; i >= 0; --i)
		markerButtons[i].Remove();
	markerButtons.Clear();
	markerCount = count;
	for(int i = 0; i < count; ++i) {
		Button& b = markerButtons.Create<Button>();
		b.SetLabel(FormatInt(i + 1));
		Add(b);
	}
	Layout();
}

ActivityMetersPane::ActivityMetersPane() {
	midiIn.Vertical();
	midiOut.Vertical();
	midiIn.SetLimits(0, 100);
	midiOut.SetLimits(0, 100);
	Add(midiIn);
	Add(midiOut);
	for(int i = 0; i < 4; ++i) {
		ProgressIndicator& meter = audioMeters.Add();
		meter.Vertical();
		meter.SetLimits(0, 100);
		Label& led = clipLeds.Add();
		led.SetLabel(" ");
		Add(led);
		Add(meter);
	}
}

void ActivityMetersPane::Layout() {
	Size sz = GetSize();
	midiIn.SetRect(0, 0, 16, sz.cy - 16);
	midiOut.SetRect(20, 0, 16, sz.cy - 16);
	int baseX = 44;
	for(int i = 0; i < audioMeters.GetCount(); ++i) {
		audioMeters[i].SetRect(baseX + i * 20, 0, 16, sz.cy - 20);
		clipLeds[i].SetRect(baseX + i * 20, sz.cy - 18, 16, 16);
	}
}

void ActivityMetersPane::SetMidiActivity(int inLevel, int outLevel) {
	midiIn.Set(max(0, min(inLevel, 100)));
	midiOut.Set(max(0, min(outLevel, 100)));
}

void ActivityMetersPane::SetAudioActivity(const Vector<int>& channels, const Vector<bool>& clipFlags) {
	int count = min(channels.GetCount(), audioMeters.GetCount());
	for(int i = 0; i < count; ++i) {
		audioMeters[i].Set(max(0, min(channels[i], 100)));
		clipLeds[i].Ink(clipFlags.GetCount() > i && clipFlags[i] ? SLtRed : SColorPaper());
	}
}

MasterOutputPane::MasterOutputPane() {
	compactSlider.Vertical();
	compactSlider.SetLimits(0, 1000);
	expandedSlider.Vertical();
	expandedSlider.SetLimits(0, 1000);
	Add(compactSlider.SizePos());
	Add(expandedSlider.RightPos(0, 24).VSizePos(0, 0));
	expandedSlider.Hide();
}

void MasterOutputPane::SetGain(double gain) {
	int v = int(gain * 1000.0);
	v = max(0, min(v, 1000));
	compactSlider.Set(v);
	expandedSlider.Set(v);
}

void MasterOutputPane::ShowExpanded(bool show) {
	expanded = show;
	expandedSlider.Show(expanded);
}

VirtualKeyboardPane::VirtualKeyboardPane() {
	Add(octaveSelector);
	octaveSelector.SetText("Octave 3");
	BuildQwertyLayout();
}

void VirtualKeyboardPane::Layout() {
	Size sz = GetSize();
	octaveSelector.SetRect(0, 0, sz.cx, 24);
	int y = 28;
	int keyWidth = whiteKeys.GetCount() ? (sz.cx - 60) / whiteKeys.GetCount() : 40;
	for(int i = 0; i < whiteKeys.GetCount(); ++i)
		whiteKeys[i].SetRect(30 + i * keyWidth, y, keyWidth - 4, 36);
	int blackWidth = keyWidth / 2;
	for(int i = 0; i < blackKeys.GetCount(); ++i)
		blackKeys[i].SetRect(30 + i * keyWidth + keyWidth / 2, y - 12, blackWidth, 24);
	velocitySlider.SetRect(sz.cx - 20, y, 16, sz.cy - y);
	modWheelA.SetRect(0, y, 16, sz.cy - y);
	modWheelB.SetRect(18, y, 16, sz.cy - y);
}

void VirtualKeyboardPane::ToggleMode() {
	SetVisibleMode(!pianoMode);
}

void VirtualKeyboardPane::SetVisibleMode(bool pianoGraphics) {
	pianoMode = pianoGraphics;
	for(Button& b : whiteKeys)
		b.Show(!pianoMode);
	for(Button& b : blackKeys)
		b.Show(!pianoMode);
	velocitySlider.Show(pianoMode);
	modWheelA.Show(pianoMode);
	modWheelB.Show(pianoMode);
}

void VirtualKeyboardPane::BuildQwertyLayout() {
	static const char* whiteLabels[] = {"Q","W","E","R","T","Y","U","I"};
	for(const char* label : whiteLabels) {
		Button& key = whiteKeys.Add();
		key.SetLabel(label);
		Add(key);
	}
	static const char* blackLabels[] = {"2","3","5","6","7"};
	for(const char* label : blackLabels) {
		Button& key = blackKeys.Add();
		key.SetLabel(label);
		Add(key);
	}
	velocitySlider.SetRange(0, 127);
	velocitySlider.SetData(96);
	velocitySlider.Hide();
	Add(velocitySlider);
	modWheelA.SetVert();
	modWheelB.SetVert();
	modWheelA.Hide();
	modWheelB.Hide();
	Add(modWheelA);
	Add(modWheelB);
}

TransportWindow::TransportWindow() {
	Title("Transport");
	Sizeable(false).Zoomable(false);
	FrameLess();
	TopMost(true);
	SetRect(0, 0, 960, 140);
	BuildLayout();
}

void TransportWindow::BuildLayout() {
	Add(closeLeft);
	Add(closeRight);
	closeLeft.SetLabel("×");
	closeRight.SetLabel("×");

	Add(usageMeters);
	Add(recordingModes);
	Add(leftLocator);
	Add(rightLocator);
	Add(timeDisplay);
	Add(transportButtons);
	Add(tempoSync);
	Add(markerQuick);
	Add(activityMeters);
	Add(masterOutput);
	Add(virtualKeyboard);
	virtualKeyboard.Hide();
}

void TransportWindow::Layout() {
	Size sz = GetSize();
	closeLeft.SetRect(0, 0, 24, 24);
	closeRight.SetRect(sz.cx - 24, 0, 24, 24);
	usageMeters.SetRect(0, 24, 64, sz.cy - 24);
	recordingModes.SetRect(68, 24, 110, sz.cy - 24);
	leftLocator.SetRect(182, 24, 120, sz.cy - 24);
	rightLocator.SetRect(306, 24, 120, sz.cy - 24);
	timeDisplay.SetRect(430, 24, 220, 80);
	transportButtons.SetRect(430, 106, 220, sz.cy - 130);
	tempoSync.SetRect(656, 24, 140, sz.cy - 24);
	markerQuick.SetRect(800, 24, 150, 90);
	activityMeters.SetRect(800, 118, 150, sz.cy - 142);
	masterOutput.SetRect(sz.cx - 24, 24, 24, sz.cy - 24);
	virtualKeyboard.SetRect(0, sz.cy - 120, sz.cx, 120);
}

void TransportWindow::SetAlwaysOnTop(bool topmost) {
	TopMost(topmost);
}

void TransportWindow::SetUsageMeters(double asioLoad, double diskLoad, bool asioOverload, bool diskOverload) {
	usageMeters.SetUsage(asioLoad, diskLoad, asioOverload, diskOverload);
}

void TransportWindow::SetRecordingModes(const String& linear, const Vector<String>& linearOptions,
	                                     const String& cycle, const Vector<String>& cycleOptions,
	                                     bool autoQuantize) {
	recordingModes.SetLinearModeOptions(linearOptions);
	recordingModes.SetCycleModeOptions(cycleOptions);
	recordingModes.SetState(linear, cycle, autoQuantize);
}

void TransportWindow::SetLeftLocator(const String& time, const String& preRoll, bool punchIn) {
	leftLocator.SetCaption("Left Locator");
	leftLocator.SetLocatorTime(time);
	leftLocator.SetRollOffset(preRoll);
	leftLocator.SetPunchEnabled(punchIn);
}

void TransportWindow::SetRightLocator(const String& time, const String& postRoll, bool punchOut) {
	rightLocator.SetCaption("Right Locator");
	rightLocator.SetLocatorTime(time);
	rightLocator.SetRollOffset(postRoll);
	rightLocator.SetPunchEnabled(punchOut);
}

void TransportWindow::SetPrimaryTime(const String& primary, const String& format, const String& secondary) {
	timeDisplay.SetPrimaryTime(primary);
	timeDisplay.SetPrimaryFormat(format);
	timeDisplay.SetSecondaryTime(secondary);
}

void TransportWindow::SetSlider(int position, int total) {
	timeDisplay.SetSliderPosition(position, total);
}

void TransportWindow::SetTransportState(bool cycle, bool playing, bool recording) {
	transportButtons.SetState(cycle, playing, recording);
}

void TransportWindow::SetTempoState(bool tempoTrack, const String& signature, const String& tempoValue) {
	tempoSync.SetTempoState(tempoTrack, signature, tempoValue);
}

void TransportWindow::SetSyncState(bool externalSync) {
	tempoSync.SetSyncState(externalSync);
}

void TransportWindow::SetMarkers(int count, const Vector<bool>& active) {
	markerQuick.SetMarkerCount(count);
	for(int i = 0; i < active.GetCount(); ++i)
		markerQuick.SetMarkerActive(i, active[i]);
}

void TransportWindow::SetMidiActivity(int inLevel, int outLevel) {
	activityMeters.SetMidiActivity(inLevel, outLevel);
}

void TransportWindow::SetAudioActivity(const Vector<int>& channels, const Vector<bool>& clipFlags) {
	activityMeters.SetAudioActivity(channels, clipFlags);
}

void TransportWindow::SetMasterGain(double gain, bool expanded) {
	masterOutput.SetGain(gain);
	masterOutput.ShowExpanded(expanded);
}

void TransportWindow::ToggleVirtualKeyboard(bool showPianoMode) {
	virtualKeyboard.Show(true);
	virtualKeyboard.SetVisibleMode(showPianoMode);
}

}
