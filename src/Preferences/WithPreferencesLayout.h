#ifndef _Preferences_WithPreferencesLayout_h_
#define _Preferences_WithPreferencesLayout_h_

#include <CtrlLib/CtrlLib.h>

// Forward declare the classes we need
namespace am {
	class PreferencesDlg;
}

// Define the WithProgressLayout template
template <class TBase>
class WithProgressLayout : public TBase {
public:
	WithProgressLayout();
	
	// UI elements
	Upp::TreeCtrl tree;
	Upp::Splitter main_splitter;
	Upp::ParentCtrl right_panel;
	Upp::DropList presets_list;
	Upp::Button preset_save_btn;
	Upp::Button preset_rename_btn;
	Upp::Button preset_delete_btn;
	Upp::Button preset_open_btn;
	Upp::Option preset_marked_only;
	Upp::Button apply;
	Upp::Button ok;
	Upp::Button cancel;
	Upp::Button defaults;
	Upp::Button help;
	
	// View holder for preference panels
	Upp::ParentCtrl view_holder;
	
protected:
	virtual void InitLayout();
};

// Remove the layout file inclusion since we're creating UI programmatically
// #define LAYOUTFILE <Preferences/WithPreferencesLayout.lay>
// #include <CtrlCore/lay.h>

#endif