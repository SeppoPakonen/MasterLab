#ifndef _Preferences_KeyCommandsPrefPane_h_
#define _Preferences_KeyCommandsPrefPane_h_

#include "../PrefUI.h"
#include "../KeyCommandsDlg.h"

namespace am {

// Key Commands Preference Panel - for inclusion in the Preferences dialog
class KeyCommandsPrefPane : public PreferencesPane {
public:
	typedef KeyCommandsPrefPane CLASSNAME;
	KeyCommandsPrefPane();
	
	// Panel lifecycle methods
	virtual void Init(PreferencesModel& model) override;
	virtual void Load(const PreferencesModel& model) override;
	virtual void Store(PreferencesModel& model, Upp::Vector<bool>& changed) override;
	
private:
	void OnKeyCommandsButton();
	
	// UI Controls
	Button keyCommandsButton;
	WithPresetsLayout layout;
};

}

#endif