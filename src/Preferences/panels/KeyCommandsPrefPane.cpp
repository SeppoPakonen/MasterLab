#include "../panels/KeyCommandsPrefPane.h"

namespace am {

KeyCommandsPrefPane::KeyCommandsPrefPane() {
	keyCommandsButton.SetLabel("Open Key Commands Editor...");
	keyCommandsButton.WhenAction = THISBACK(OnKeyCommandsButton);
	
	// Add the button to the control
	Add(keyCommandsButton.SizePos());
}

void KeyCommandsPrefPane::Init(PreferencesModel& model) {
	// Initialize the key commands preference panel
	// This is called when the panel is first created
}

void KeyCommandsPrefPane::Load(const PreferencesModel& model) {
	// Load the current key command settings into the UI
	// For now, our UI is just a button that opens the key commands dialog
}

void KeyCommandsPrefPane::Store(PreferencesModel& model, Upp::Vector<bool>& changed) {
	// Store the key command settings from the UI to the model
	// Since our UI is just a button for opening the editor, there's nothing to store directly
}

void KeyCommandsPrefPane::OnKeyCommandsButton() {
	// Open the key commands dialog when the button is clicked
	KeyCommandsDlg dlg;
	dlg.Run(*this);
}

// Register this panel with the panel registry
// This creates an instance of the registrar at program startup
static struct KeyCommandsPrefPaneRegistrar {
	KeyCommandsPrefPaneRegistrar() {
		PanelRegistry::Instance().RegisterPanel("Key Commands", "All Commands", []() { return new KeyCommandsPrefPane(); });
	}
} key_commands_pref_pane_registrar;

}