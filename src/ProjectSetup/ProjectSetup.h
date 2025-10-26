#ifndef _ProjectSetup_ProjectSetup_h_
#define _ProjectSetup_ProjectSetup_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

struct ProjectSetupModel {
	String start;
	String length;
	String frameRate;
	String displayFormat;
	String displayOffset;
	int barOffset = 0;
	int sampleRate = 44100;
	int recordBitDepth = 24;
	String recordFileType = "Wave";
	String stereoPanLaw = "Equal Power";
};

class ProjectSetupValidator {
public:
	static bool Validate(const ProjectSetupModel& model, String& error);
};

class ProjectSetupDialog : public TopWindow {
public:
	typedef ProjectSetupDialog CLASSNAME;
	ProjectSetupDialog();

	void SetModel(const ProjectSetupModel& model);
	ProjectSetupModel GetModel() const;

	Event<> WhenHelp;
	Event<const ProjectSetupModel&> WhenApply;

private:
	void BuildLayout();
	void PopulateDefaults();
	void OnHelp();
	void OnOK();
	void OnCancel();
	void OnDisplayFormatChange();

	EditString startField;
	EditString lengthField;
	DropList frameRateDrop;
	DropList displayFormatDrop;
	EditString displayOffsetField;
	EditIntSpin barOffsetField;
	DropList sampleRateDrop;
	DropList recordBitDepthDrop;
	DropList recordFileTypeDrop;
	DropList panLawDrop;
	Button helpButton;
	Button okButton;
	Button cancelButton;
};

}

#endif
