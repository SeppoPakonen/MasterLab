#include "Preferences.h"
#include <ProjectMgmt/AK.h>  // Include AK definitions
namespace am {

// Define command IDs for key commands
enum KeyCommandIds {
	AKKeys::AK_FILE_NEW_PROJECT = 1,
	AKKeys::AK_FILE_OPEN = 2,
	AKKeys::AK_FILE_SAVE = 3,
	AKKeys::AKKeys::AK_FILE_SAVE_AS = 4,
	AKKeys::AK_FILE_CLOSE = 5,
	AKKeys::AK_FILE_EXPORT_AUDIO_MIXDOWN = 6,
	
	AKKeys::AK_EDIT_UNDO = 7,
	AKKeys::AK_EDIT_REDO = 8,
	AKKeys::AK_EDIT_CUT = 9,
	AKKeys::AK_EDIT_COPY = 10,
	AKKeys::AK_EDIT_PASTE = 11,
	AKKeys::AK_EDIT_DELETE = 12,
	
	AKKeys::AK_TRANSPORT_PLAY = 13,
	AKKeys::AK_TRANSPORT_STOP = 14,
	AKKeys::AK_TRANSPORT_RECORD = 15,
	
	AKKeys::AK_PREFERENCES_OPEN = 16,
	AKKeys::AK_PROJECT_SETUP = 17,
	AKKeys::AK_MEDIA_OPEN_POOL = 18,
	
	AKKeys::AK_AUDIO_NORMALIZE = 19,
	AKKeys::AK_AUDIO_GAIN = 20,
	
	AKKeys::AK_MIDI_QUANTIZE = 21,
	AKKeys::AK_MIDI_TRANSPOSE = 22
};

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
		case AKKeys::AK_FILE_NEW_PROJECT: return "File/New Project";
		case AKKeys::AK_FILE_OPEN: return "File/Open...";
		case AKKeys::AK_FILE_SAVE: return "File/Save";
		case AKKeys::AKKeys::AK_FILE_SAVE_AS: return "File/Save As...";
		case AKKeys::AK_FILE_CLOSE: return "File/Close";
		case AKKeys::AK_FILE_EXPORT_AUDIO_MIXDOWN: return "File/Export Audio Mixdown...";
		
		case AKKeys::AK_EDIT_UNDO: return "Edit/Undo";
		case AKKeys::AK_EDIT_REDO: return "Edit/Redo";
		case AKKeys::AK_EDIT_CUT: return "Edit/Cut";
		case AKKeys::AK_EDIT_COPY: return "Edit/Copy";
		case AKKeys::AK_EDIT_PASTE: return "Edit/Paste";
		case AKKeys::AK_EDIT_DELETE: return "Edit/Delete";
		
		case AKKeys::AK_TRANSPORT_PLAY: return "Transport/Play";
		case AKKeys::AK_TRANSPORT_STOP: return "Transport/Stop";
		case AKKeys::AK_TRANSPORT_RECORD: return "Transport/Record";
		
		case AKKeys::AK_PREFERENCES_OPEN: return "File/Preferences...";
		case AKKeys::AK_PROJECT_SETUP: return "Project/Project Setup...";
		case AKKeys::AK_MEDIA_OPEN_POOL: return "Media/Open Pool Window";
		default: return "Unknown Command";
	}
}

int KeyCommands::GetKeyId(const String& key_name) const {
	// In a real implementation, this would map readable names to key IDs
	// For now, we'll return a placeholder
	if(key_name == "File/New Project") return AKKeys::AK_FILE_NEW_PROJECT;
	if(key_name == "File/Open...") return AKKeys::AK_FILE_OPEN;
	if(key_name == "File/Save") return AKKeys::AK_FILE_SAVE;
	if(key_name == "File/Save As...") return AKKeys::AKKeys::AK_FILE_SAVE_AS;
	if(key_name == "File/Close") return AKKeys::AK_FILE_CLOSE;
	if(key_name == "File/Export Audio Mixdown...") return AKKeys::AK_FILE_EXPORT_AUDIO_MIXDOWN;
	if(key_name == "Edit/Undo") return AKKeys::AK_EDIT_UNDO;
	if(key_name == "Edit/Redo") return AKKeys::AK_EDIT_REDO;
	if(key_name == "Edit/Cut") return AKKeys::AK_EDIT_CUT;
	if(key_name == "Edit/Copy") return AKKeys::AK_EDIT_COPY;
	if(key_name == "Edit/Paste") return AKKeys::AK_EDIT_PASTE;
	if(key_name == "Edit/Delete") return AKKeys::AK_EDIT_DELETE;
	if(key_name == "Transport/Play") return AKKeys::AK_TRANSPORT_PLAY;
	if(key_name == "Transport/Stop") return AKKeys::AK_TRANSPORT_STOP;
	if(key_name == "Transport/Record") return AKKeys::AK_TRANSPORT_RECORD;
	if(key_name == "File/Preferences...") return AKKeys::AK_PREFERENCES_OPEN;
	if(key_name == "Project/Project Setup...") return AKKeys::AK_PROJECT_SETUP;
	if(key_name == "Media/Open Pool Window") return AKKeys::AK_MEDIA_OPEN_POOL;
	
	return -1; // Not found
}

}
