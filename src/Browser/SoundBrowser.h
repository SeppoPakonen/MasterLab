#ifndef _Browser_SoundBrowser_h_
#define _Browser_SoundBrowser_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

class SoundBrowser : public TopWindow {
public:
	typedef SoundBrowser CLASSNAME;
	SoundBrowser();
	
	void Open();
	void Close();
	void Refresh();
	
private:
	void Init();
	
	// UI elements would go here
};

}

#endif