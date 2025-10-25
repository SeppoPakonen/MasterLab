#ifndef _Windowing_Workspace_h_
#define _Windowing_Workspace_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

struct WindowLayout {
	String window_name;
	Rect position;
	bool visible;
};

class Workspace {
public:
	Workspace();
	void SaveLayout();
	void RestoreLayout();
	void LockLayout(bool lock);
	bool IsLayoutLocked() const { return layout_locked; }
	void OrganizeLayout();
	Vector<String> GetAvailableLayouts() const { return available_layouts; }
	
private:
	Vector<WindowLayout> current_layout;
	Vector<String> available_layouts;
	bool layout_locked = false;
};

}

#endif