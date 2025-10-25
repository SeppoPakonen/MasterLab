#ifndef _MediaPool_PoolWindow_h_
#define _MediaPool_PoolWindow_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

class PoolWindow : public TopWindow {
public:
	typedef PoolWindow CLASSNAME;
	PoolWindow();
	
	void Open();
	void Close();
	void Refresh();
	
private:
	void Init();
	
	// UI elements would go here
};

}

#endif