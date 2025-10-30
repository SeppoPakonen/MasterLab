#ifndef _HelpAbout_Registration_h_
#define _HelpAbout_Registration_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

class Registration {
public:
	Registration();
	bool IsRegistered() const { return registered; }
	bool Register(const Upp::String& key);
	Upp::String GetRegistrationKey() const { return registration_key; }
	void ShowRegistrationDialog();
	
private:
	bool registered = false;
	Upp::String registration_key;
};

}

#endif