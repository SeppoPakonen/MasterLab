#ifndef _Browser_LoopBrowser_h_
#define _Browser_LoopBrowser_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

class LoopBrowser : public TopWindow {
public:
	typedef LoopBrowser CLASSNAME;
	LoopBrowser();
	
	void Open();
	void Close();
	void Refresh();
	
private:
	void Init();
	
	// UI elements would go here
};

}

#endif