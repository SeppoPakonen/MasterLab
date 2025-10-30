#include "Preferences.h"
#include <ProjectMgmt/AK.h>  // Include AK definitions
namespace am {

KeyCommands::KeyCommands() {
	// Initialize key command system
}

void KeyCommands::LoadCommands() {
	LOG("Loading key commands");
	
	// Load key command mappings from storage
	// For now, initialize with defaults from the AK.key file
	
	// Clear existing commands
	commands.Clear();
	
	// Add default key commands
	// Using placeholder integer values for now until we understand how AKKeys works
	AddCommand(KeyCommand(1, "Ctrl+N", "File/New Project"));
	AddCommand(KeyCommand(2, "Ctrl+O", "File/Open..."));
	AddCommand(KeyCommand(3, "Ctrl+S", "File/Save"));
	AddCommand(KeyCommand(4, "Ctrl+Shift+S", "File/Save As..."));
	AddCommand(KeyCommand(5, "Ctrl+W", "File/Close"));
	AddCommand(KeyCommand(6, "Ctrl+Shift+E", "File/Export Audio Mixdown..."));
	
	AddCommand(KeyCommand(7, "Ctrl+Z", "Edit/Undo"));
	AddCommand(KeyCommand(8, "Ctrl+Y", "Edit/Redo"));
	AddCommand(KeyCommand(9, "Ctrl+X", "Edit/Cut"));
	AddCommand(KeyCommand(10, "Ctrl+C", "Edit/Copy"));
	AddCommand(KeyCommand(11, "Ctrl+V", "Edit/Paste"));
	AddCommand(KeyCommand(12, "Del", "Edit/Delete"));
	
	AddCommand(KeyCommand(13, "Space", "Transport/Play"));
	AddCommand(KeyCommand(14, "Ctrl+Space", "Transport/Stop"));
	AddCommand(KeyCommand(15, "R", "Transport/Record"));
	
	AddCommand(KeyCommand(16, "Ctrl+,", "File/Preferences..."));
	AddCommand(KeyCommand(17, "", "Project/Project Setup..."));
	AddCommand(KeyCommand(18, "", "Media/Open Pool Window"));
}

void KeyCommands::SaveCommands() {
	LOG("Saving key commands");
	// Stub - implement actual command saving
}

void KeyCommands::AddCommand(const KeyCommand& cmd) {
	commands.Add(cmd);
}

void KeyCommands::RemoveCommand(int commandId) {
	for(int i = 0; i < commands.GetCount(); i++) {
		if(commands[i].command_id == commandId) {
			commands.Remove(i);
			break;
		}
	}
}

void KeyCommands::UpdateCommand(int commandId, const Upp::String& newKeySequence) {
	for(int i = 0; i < commands.GetCount(); i++) {
		if(commands[i].command_id == commandId) {
			commands[i].key_sequence = newKeySequence;
			break;
		}
	}
}

Upp::String KeyCommands::GetKeyName(int key_id) const {
	// In a real implementation, this would map key IDs to readable names
	// For now, we'll return a placeholder
	switch(key_id) {
		case 1: return "File/New Project";
		case 2: return "File/Open...";
		case 3: return "File/Save";
		case 4: return "File/Save As...";
		case 5: return "File/Close";
		case 6: return "File/Export Audio Mixdown...";
		
		case 7: return "Edit/Undo";
		case 8: return "Edit/Redo";
		case 9: return "Edit/Cut";
		case 10: return "Edit/Copy";
		case 11: return "Edit/Paste";
		case 12: return "Edit/Delete";
		
		case 13: return "Transport/Play";
		case 14: return "Transport/Stop";
		case 15: return "Transport/Record";
		
		case 16: return "File/Preferences...";
		case 17: return "Project/Project Setup...";
		case 18: return "Media/Open Pool Window";
		default: return "Unknown Command";
	}
}

int KeyCommands::GetKeyId(const Upp::String& key_name) const {
	// In a real implementation, this would map readable names to key IDs
	// For now, we'll return a placeholder
	if(key_name == "File/New Project") return 1;
	if(key_name == "File/Open...") return 2;
	if(key_name == "File/Save") return 3;
	if(key_name == "File/Save As...") return 4;
	if(key_name == "File/Close") return 5;
	if(key_name == "File/Export Audio Mixdown...") return 6;
	if(key_name == "Edit/Undo") return 7;
	if(key_name == "Edit/Redo") return 8;
	if(key_name == "Edit/Cut") return 9;
	if(key_name == "Edit/Copy") return 10;
	if(key_name == "Edit/Paste") return 11;
	if(key_name == "Edit/Delete") return 12;
	if(key_name == "Transport/Play") return 13;
	if(key_name == "Transport/Stop") return 14;
	if(key_name == "Transport/Record") return 15;
	if(key_name == "File/Preferences...") return 16;
	if(key_name == "Project/Project Setup...") return 17;
	if(key_name == "Media/Open Pool Window") return 18;
	
	return -1; // Not found
}

}