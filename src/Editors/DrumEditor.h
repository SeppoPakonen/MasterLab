#ifndef _Editors_DrumEditor_h_
#define _Editors_DrumEditor_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

class DrumEditor : public TopWindow {
public:
	typedef DrumEditor CLASSNAME;
	DrumEditor();
	
	void Open();
	void Close();
	void SetData(void* data);
	
private:
	void Init();
	
	// UI elements would go here
};

}

#endif