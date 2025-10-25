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
	WithLayout<> layout;
	layout.SetRect(0, 0, 400, 200);
	layout.AddPrompt("Enter registration key:");
	LineEdit regKey;
	layout.Add(regKey);
	
	Button okBtn("OK");
	layout.Add(okBtn);
	
	Ctrl dlg;
	dlg.Add(layout.SizePos());
	
	okBtn <<= [&] {
		if(Register(regKey.GetData())) {
			PromptOK("Registration", "Registration successful!");
			dlg.Break();
		} else {
			PromptOK("Registration", "Invalid registration key!");
		}
	};
	
	dlg.Run();
}

}