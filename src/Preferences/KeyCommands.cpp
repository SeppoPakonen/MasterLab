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
	AddCommand({AKKeys::FILE_NEW_PROJECT, "Ctrl+N", "File/New Project"});
	AddCommand({AKKeys::FILE_OPEN, "Ctrl+O", "File/Open..."});
	AddCommand({AKKeys::FILE_SAVE, "Ctrl+S", "File/Save"});
	AddCommand({AKKeys::FILE_SAVE_AS, "Ctrl+Shift+S", "File/Save As..."});
	AddCommand({AKKeys::FILE_CLOSE, "Ctrl+W", "File/Close"});
	AddCommand({AKKeys::FILE_EXPORT_AUDIO_MIXDOWN, "Ctrl+Shift+E", "File/Export Audio Mixdown..."});
	
	AddCommand({AKKeys::EDIT_UNDO, "Ctrl+Z", "Edit/Undo"});
	AddCommand({AKKeys::EDIT_REDO, "Ctrl+Y", "Edit/Redo"});
	AddCommand({AKKeys::EDIT_CUT, "Ctrl+X", "Edit/Cut"});
	AddCommand({AKKeys::EDIT_COPY, "Ctrl+C", "Edit/Copy"});
	AddCommand({AKKeys::EDIT_PASTE, "Ctrl+V", "Edit/Paste"});
	AddCommand({AKKeys::EDIT_DELETE, "Del", "Edit/Delete"});
	
	AddCommand({AKKeys::TRANSPORT_PLAY, "Space", "Transport/Play"});
	AddCommand({AKKeys::TRANSPORT_STOP, "Ctrl+Space", "Transport/Stop"});
	AddCommand({AKKeys::TRANSPORT_RECORD, "R", "Transport/Record"});
	
	AddCommand({AKKeys::PREFERENCES_OPEN, "Ctrl+,", "File/Preferences..."});
	AddCommand({AKKeys::PROJECT_SETUP, "", "Project/Project Setup..."});
	AddCommand({AKKeys::MEDIA_OPEN_POOL, "", "Media/Open Pool Window"});
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

void KeyCommands::UpdateCommand(int commandId, const String& newKeySequence) {
	for(int i = 0; i < commands.GetCount(); i++) {
		if(commands[i].command_id == commandId) {
			commands[i].key_sequence = newKeySequence;
			break;
		}
	}
}

String KeyCommands::GetKeyName(int key_id) const {
	// In a real implementation, this would map key IDs to readable names
	// For now, we'll return a placeholder
	switch(key_id) {
		case AKKeys::FILE_NEW_PROJECT: return "File/New Project";
		case AKKeys::FILE_OPEN: return "File/Open...";
		case AKKeys::FILE_SAVE: return "File/Save";
		case AKKeys::FILE_SAVE_AS: return "File/Save As...";
		case AKKeys::FILE_CLOSE: return "File/Close";
		case AKKeys::FILE_EXPORT_AUDIO_MIXDOWN: return "File/Export Audio Mixdown...";
		case AKKeys::EDIT_UNDO: return "Edit/Undo";
		case AKKeys::EDIT_REDO: return "Edit/Redo";
		case AKKeys::EDIT_CUT: return "Edit/Cut";
		case AKKeys::EDIT_COPY: return "Edit/Copy";
		case AKKeys::EDIT_PASTE: return "Edit/Paste";
		case AKKeys::EDIT_DELETE: return "Edit/Delete";
		case AKKeys::TRANSPORT_PLAY: return "Transport/Play";
		case AKKeys::TRANSPORT_STOP: return "Transport/Stop";
		case AKKeys::TRANSPORT_RECORD: return "Transport/Record";
		case AKKeys::PREFERENCES_OPEN: return "File/Preferences...";
		case AKKeys::PROJECT_SETUP: return "Project/Project Setup...";
		case AKKeys::MEDIA_OPEN_POOL: return "Media/Open Pool Window";
		default: return "Unknown Command";
	}
}

int KeyCommands::GetKeyId(const String& key_name) const {
	// In a real implementation, this would map readable names to key IDs
	// For now, we'll return a placeholder
	if(key_name == "File/New Project") return AKKeys::FILE_NEW_PROJECT;
	if(key_name == "File/Open...") return AKKeys::FILE_OPEN;
	if(key_name == "File/Save") return AKKeys::FILE_SAVE;
	if(key_name == "File/Save As...") return AKKeys::FILE_SAVE_AS;
	if(key_name == "File/Close") return AKKeys::FILE_CLOSE;
	if(key_name == "File/Export Audio Mixdown...") return AKKeys::FILE_EXPORT_AUDIO_MIXDOWN;
	if(key_name == "Edit/Undo") return AKKeys::EDIT_UNDO;
	if(key_name == "Edit/Redo") return AKKeys::EDIT_REDO;
	if(key_name == "Edit/Cut") return AKKeys::EDIT_CUT;
	if(key_name == "Edit/Copy") return AKKeys::EDIT_COPY;
	if(key_name == "Edit/Paste") return AKKeys::EDIT_PASTE;
	if(key_name == "Edit/Delete") return AKKeys::EDIT_DELETE;
	if(key_name == "Transport/Play") return AKKeys::TRANSPORT_PLAY;
	if(key_name == "Transport/Stop") return AKKeys::TRANSPORT_STOP;
	if(key_name == "Transport/Record") return AKKeys::TRANSPORT_RECORD;
	if(key_name == "File/Preferences...") return AKKeys::PREFERENCES_OPEN;
	if(key_name == "Project/Project Setup...") return AKKeys::PROJECT_SETUP;
	if(key_name == "Media/Open Pool Window") return AKKeys::MEDIA_OPEN_POOL;
	
	return -1; // Not found
}

}
