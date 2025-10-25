#include "Windowing.h"
namespace am {

Workspace::Workspace() {
	// Initialize with default layout names
	available_layouts.Add("Default");
	available_layouts.Add("Mixing");
	available_layouts.Add("Editing");
	available_layouts.Add("Scoring");
}

void Workspace::SaveLayout() {
	LOG("Saving workspace layout");
	// Stub - implement actual layout saving
}

void Workspace::RestoreLayout() {
	LOG("Restoring workspace layout");
	// Stub - implement actual layout restoration
}

void Workspace::LockLayout(bool lock) {
	layout_locked = lock;
}

void Workspace::OrganizeLayout() {
	LOG("Organizing workspace layout");
	// Stub - implement actual layout organization
}

}