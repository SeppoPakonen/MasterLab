#ifndef _Editors_ListEditor_h_
#define _Editors_ListEditor_h_

#ifdef flagGUI
#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

class ListEditor : public TopWindow {
public:
	typedef ListEditor CLASSNAME;
	ListEditor();
	
	void Open();
	void Close();
	void SetData(void* data);
	
private:
	void Init();
	
	// UI elements would go here
};

}
#endif // GUI

#endif
