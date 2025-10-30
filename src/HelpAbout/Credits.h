#ifndef _HelpAbout_Credits_h_
#define _HelpAbout_Credits_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

class Credits {
public:
	Credits();
	Upp::String GetCreditsText() const;
	void ShowCredits();
	
private:
	Upp::String credits;
};

}

#endif