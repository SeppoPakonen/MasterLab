#ifndef _Browser_MediaBay_h_
#define _Browser_MediaBay_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

class MediaBay : public TopWindow {
public:
	typedef MediaBay CLASSNAME;
	MediaBay();
	
	void Open();
	void Close();
	void Refresh();
	
private:
	void Init();
	
	// UI elements would go here
};

}

#endif