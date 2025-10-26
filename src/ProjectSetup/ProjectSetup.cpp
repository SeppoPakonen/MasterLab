#include "ProjectSetup.h"

namespace am {

bool ProjectSetupValidator::Validate(const ProjectSetupModel& model, String& error) {
	if(IsNull(model.start) || IsNull(model.length)) {
		error = "Start and Length must be specified.";
		return false;
	}
	return true;
}

ProjectSetupDialog::ProjectSetupDialog() {
	Title("Project Setup");
	Size(Size(380, 320));
	MinimizeBox(false);
	MaximizeBox(false);
	Sizeable(false);
	Zoomable(false);
	BuildLayout();
	PopulateDefaults();

	helpButton.WhenAction = THISBACK(OnHelp);
	okButton.WhenAction = THISBACK(OnOK);
	cancelButton.WhenAction = THISBACK(OnCancel);
	displayFormatDrop.WhenAction = THISBACK(OnDisplayFormatChange);
}

void ProjectSetupDialog::BuildLayout() {
	int left = 16;
	int labelWidth = 120;

	Add(Label("Start:").TopPos(16, 20).LeftPos(left, labelWidth));
	Add(startField.TopPos(16, 20).LeftPos(left + labelWidth, 160));

	Add(Label("Length:").TopPos(44, 20).LeftPos(left, labelWidth));
	Add(lengthField.TopPos(44, 20).LeftPos(left + labelWidth, 160));

	Add(Label("Frame Rate:").TopPos(84, 20).LeftPos(left, labelWidth));
	Add(frameRateDrop.TopPos(84, 20).LeftPos(left + labelWidth, 160));

	Add(Label("Display Format:").TopPos(112, 20).LeftPos(left, labelWidth));
	Add(displayFormatDrop.TopPos(112, 20).LeftPos(left + labelWidth, 160));

	Add(Label("Display Offset:").TopPos(140, 20).LeftPos(left, labelWidth));
	Add(displayOffsetField.TopPos(140, 20).LeftPos(left + labelWidth, 160));

	Add(Label("Bar Offset:").TopPos(168, 20).LeftPos(left, labelWidth));
	Add(barOffsetField.TopPos(168, 20).LeftPos(left + labelWidth, 80));

	Add(Label("Sample Rate:").TopPos(208, 20).LeftPos(left, labelWidth));
	Add(sampleRateDrop.TopPos(208, 20).LeftPos(left + labelWidth, 160));

	Add(Label("Record Bit Depth:").TopPos(236, 20).LeftPos(left, labelWidth));
	Add(recordBitDepthDrop.TopPos(236, 20).LeftPos(left + labelWidth, 160));

	Add(Label("Record File Type:").TopPos(264, 20).LeftPos(left, labelWidth));
	Add(recordFileTypeDrop.TopPos(264, 20).LeftPos(left + labelWidth, 160));

	Add(Label("Stereo Pan Law:").TopPos(292, 20).LeftPos(left, labelWidth));
	Add(panLawDrop.TopPos(292, 20).LeftPos(left + labelWidth, 160));

	helpButton.SetLabel("Help");
	Add(helpButton.BottomPos(12, 24).LeftPos(left, 80));

	okButton.SetLabel("OK");
	Add(okButton.BottomPos(12, 24).RightPos(108, 80));

	cancelButton.SetLabel("Cancel");
	Add(cancelButton.BottomPos(12, 24).RightPos(16, 80));
}

void ProjectSetupDialog::PopulateDefaults() {
	startField.SetData("00:00:00:00");
	lengthField.SetData("00:10:00:00");
	frameRateDrop.Add("23.976 fps");
	frameRateDrop.Add("24 fps");
	frameRateDrop.Add("25 fps");
	frameRateDrop.Add("29.97 fps");
	frameRateDrop.Add("30 fps");
	frameRateDrop.SetIndex(1);

	displayFormatDrop.Add("Bars+Beats");
	displayFormatDrop.Add("Seconds");
	displayFormatDrop.Add("Timecode");
	displayFormatDrop.Add("Samples");
	displayFormatDrop.Add("60fps (user)");
	displayFormatDrop.SetIndex(0);

	displayOffsetField.SetData("00:00:00:00");
	barOffsetField.SetData(0);

	sampleRateDrop.Add(32000, "32.0 kHz");
	sampleRateDrop.Add(44100, "44.1 kHz");
	sampleRateDrop.Add(48000, "48.0 kHz");
	sampleRateDrop.Add(64000, "64.0 kHz");
	sampleRateDrop.Add(88200, "88.2 kHz");
	sampleRateDrop.Add(96000, "96.0 kHz");
	sampleRateDrop.SetData(44100);

	recordBitDepthDrop.Add(16, "16-bit");
	recordBitDepthDrop.Add(24, "24-bit");
	recordBitDepthDrop.Add(32, "32-bit float");
	recordBitDepthDrop.SetData(24);

	recordFileTypeDrop.Add("Wave");
	recordFileTypeDrop.Add("Broadcast Wave");
	recordFileTypeDrop.Add("AIFF");
	recordFileTypeDrop.Add("Wave64");
	recordFileTypeDrop.SetIndex(0);

	panLawDrop.Add("Equal Power");
	panLawDrop.Add("0 dB");
	panLawDrop.Add("-3 dB");
	panLawDrop.Add("-4.5 dB");
	panLawDrop.Add("-6 dB");
	panLawDrop.SetIndex(0);
}

void ProjectSetupDialog::SetModel(const ProjectSetupModel& model) {
	startField.SetData(model.start);
	lengthField.SetData(model.length);
	int frameIndex = frameRateDrop.FindText(model.frameRate);
	if(frameIndex >= 0)
		frameRateDrop.SetIndex(frameIndex);
	int displayIndex = displayFormatDrop.FindText(model.displayFormat);
	if(displayIndex >= 0)
		displayFormatDrop.SetIndex(displayIndex);
	displayOffsetField.SetData(model.displayOffset);
	barOffsetField.SetData(model.barOffset);
	sampleRateDrop.SetData(model.sampleRate);
	recordBitDepthDrop.SetData(model.recordBitDepth);
	int fileTypeIndex = recordFileTypeDrop.FindText(model.recordFileType);
	if(fileTypeIndex >= 0)
		recordFileTypeDrop.SetIndex(fileTypeIndex);
	int panIndex = panLawDrop.FindText(model.stereoPanLaw);
	if(panIndex >= 0)
		panLawDrop.SetIndex(panIndex);
}

ProjectSetupModel ProjectSetupDialog::GetModel() const {
	ProjectSetupModel model;
	model.start = startField.GetData();
	model.length = lengthField.GetData();
	model.frameRate = frameRateDrop.GetText();
	model.displayFormat = displayFormatDrop.GetText();
	model.displayOffset = displayOffsetField.GetData();
	model.barOffset = (int)barOffsetField.GetData();
	Value rate = sampleRateDrop.GetData();
	model.sampleRate = IsNull(rate) ? 44100 : (int)rate;
	Value bitDepth = recordBitDepthDrop.GetData();
	model.recordBitDepth = IsNull(bitDepth) ? 24 : (int)bitDepth;
	model.recordFileType = recordFileTypeDrop.GetText();
	model.stereoPanLaw = panLawDrop.GetText();
	return model;
}

void ProjectSetupDialog::OnHelp() {
	WhenHelp();
}

void ProjectSetupDialog::OnOK() {
	ProjectSetupModel model = GetModel();
	String error;
	if(!ProjectSetupValidator::Validate(model, error)) {
		PromptOK(error);
		return;
	}
	WhenApply(model);
	Close();
}

void ProjectSetupDialog::OnCancel() {
	Close();
}

void ProjectSetupDialog::OnDisplayFormatChange() {
	// Placeholder for future dynamic behaviour (e.g. update rulers)
}

}
