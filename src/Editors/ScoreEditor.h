#ifndef _Editors_ScoreEditor_h_
#define _Editors_ScoreEditor_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

class ScoreEditor : public TopWindow {
public:
	typedef ScoreEditor CLASSNAME;
	ScoreEditor();
	
	void Open();
	void Close();
	void SetData(void* data);
	
private:
	void Init();
	
	// UI elements would go here
};

}

#endif