#include "HelpAbout.h"
namespace am {

Registration::Registration() {
	// Initialize registration
}

bool Registration::Register(const String& key) {
	LOG("Registering with key: " + key);
	// Stub - implement actual registration validation
	if(key.GetCount() > 0) {
		registration_key = key;
		registered = true;
		return true;
	}
	return false;
}

void Registration::ShowRegistrationDialog() {
	// Create a simple registration dialog
	TopWindow dlg;
	LineEdit regKey;
	Button okBtn;
	
	dlg.Add(regKey.HSizePos(10, 10).TopPos(10, 20));
	CtrlLayoutOKCancel(dlg, "Registration");
	dlg.Add(okBtn.RightPos(10, 60).VSizePos(40, 25));
	dlg.SetRect(0, 0, 400, 120);
	dlg.Title("Registration");
	
	okBtn.SetLabel("OK");
	okBtn.WhenAction = [&] {
		if(Register(regKey.GetData())) {
			PromptOK("Registration successful!");
			dlg.Close();
		} else {
			PromptOK("Invalid registration key!");
		}
	};
	
	dlg.Run();
}

}