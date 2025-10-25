#ifndef _Editors_InPlaceEditor_h_
#define _Editors_InPlaceEditor_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

class InPlaceEditor : public TopWindow {
public:
	typedef InPlaceEditor CLASSNAME;
	InPlaceEditor();
	
	void Open();
	void Close();
	void SetData(void* data);
	
private:
	void Init();
	
	// UI elements would go here
};

}

#endif