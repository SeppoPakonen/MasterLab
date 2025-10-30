#ifndef _HelpAbout_WebLinks_h_
#define _HelpAbout_WebLinks_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

class WebLinks {
public:
	WebLinks();
	void OpenHelpSite();
	void OpenSupportSite();
	void OpenUpdatesSite();
	void OpenForumSite();
	
private:
	Upp::String help_url = "https://masterlab.example.com/help";
	Upp::String support_url = "https://masterlab.example.com/support";
	Upp::String updates_url = "https://masterlab.example.com/updates";
	Upp::String forum_url = "https://masterlab.example.com/forum";
};

}

#endif