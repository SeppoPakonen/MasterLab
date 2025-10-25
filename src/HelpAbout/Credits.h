#ifndef _HelpAbout_Credits_h_
#define _HelpAbout_Credits_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

class Credits {
public:
	Credits();
	String GetCreditsText() const;
	void ShowCredits();
	
private:
	String credits;
};

}

#endif