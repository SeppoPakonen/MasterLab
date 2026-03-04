#ifndef _Editors_KeyEditor_h_
#define _Editors_KeyEditor_h_

#ifdef GUI
#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

class KeyEditor : public TopWindow {
public:
	typedef KeyEditor CLASSNAME;
	KeyEditor();
	
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
