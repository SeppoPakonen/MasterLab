#include "Preferences.h"
#include <ProjectMgmt/AK.h>  // Include AK definitions

namespace am {

KeyCommands::KeyCommands() {
	// Initialize key command system
	LoadAKKeyDefinitions();
}

void KeyCommands::LoadCommands() {
	LOG("Loading key commands");
	
	// Load key command mappings from storage
	// For now, initialize with defaults from the AK.key file
	
	// Clear existing commands
	commands.Clear();
	
	// Add default key commands using AK keys
	AddCommand(KeyCommand(AKKeys::FILE_NEW_PROJECT, "Ctrl+N", "File/New Project"));
	AddCommand(KeyCommand(AKKeys::FILE_OPEN, "Ctrl+O", "File/Open..."));
	AddCommand(KeyCommand(AKKeys::FILE_SAVE, "Ctrl+S", "File/Save"));
	AddCommand(KeyCommand(AKKeys::FILE_SAVE_AS, "Ctrl+Shift+S", "File/Save As..."));
	AddCommand(KeyCommand(AKKeys::FILE_CLOSE, "Ctrl+W", "File/Close"));
	AddCommand(KeyCommand(AKKeys::FILE_EXPORT_AUDIO_MIXDOWN, "Ctrl+Shift+E", "File/Export Audio Mixdown..."));
	
	AddCommand(KeyCommand(AKKeys::EDIT_UNDO, "Ctrl+Z", "Edit/Undo"));
	AddCommand(KeyCommand(AKKeys::EDIT_REDO, "Ctrl+Y", "Edit/Redo"));
	AddCommand(KeyCommand(AKKeys::EDIT_CUT, "Ctrl+X", "Edit/Cut"));
	AddCommand(KeyCommand(AKKeys::EDIT_COPY, "Ctrl+C", "Edit/Copy"));
	AddCommand(KeyCommand(AKKeys::EDIT_PASTE, "Ctrl+V", "Edit/Paste"));
	AddCommand(KeyCommand(AKKeys::EDIT_DELETE, "Del", "Edit/Delete"));
	
	AddCommand(KeyCommand(AKKeys::TRANSPORT_PLAY, "Space", "Transport/Play"));
	AddCommand(KeyCommand(AKKeys::TRANSPORT_STOP, "Ctrl+Space", "Transport/Stop"));
	AddCommand(KeyCommand(AKKeys::TRANSPORT_RECORD, "R", "Transport/Record"));
	
	AddCommand(KeyCommand(AKKeys::PREFERENCES_OPEN, "Ctrl+,", "File/Preferences..."));
	AddCommand(KeyCommand(AKKeys::PROJECT_SETUP, "", "Project/Project Setup..."));
	AddCommand(KeyCommand(AKKeys::MEDIA_OPEN_POOL, "", "Media/Open Pool Window"));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_OPEN, "", "File/Key Commands..."));
}

void KeyCommands::LoadAKKeyDefinitions() {
	// Initialize with all possible AK key definitions for the key commands dialog
	// This will make all available keys visible in the preferences dialog
	commands.Clear();
	
	// File menu
	AddCommand(KeyCommand(AKKeys::FILE_NEW_PROJECT, "Ctrl+N", "File/New Project"));
	AddCommand(KeyCommand(AKKeys::FILE_OPEN, "Ctrl+O", "File/Open..."));
	AddCommand(KeyCommand(AKKeys::FILE_SAVE, "Ctrl+S", "File/Save"));
	AddCommand(KeyCommand(AKKeys::FILE_SAVE_AS, "Ctrl+Shift+S", "File/Save As..."));
	AddCommand(KeyCommand(AKKeys::FILE_CLOSE, "Ctrl+W", "File/Close"));
	AddCommand(KeyCommand(AKKeys::FILE_EXPORT_AUDIO_MIXDOWN, "Ctrl+Shift+E", "File/Export Audio Mixdown..."));
	
	// Edit menu
	AddCommand(KeyCommand(AKKeys::EDIT_UNDO, "Ctrl+Z", "Edit/Undo"));
	AddCommand(KeyCommand(AKKeys::EDIT_REDO, "Ctrl+Y", "Edit/Redo"));
	AddCommand(KeyCommand(AKKeys::EDIT_CUT, "Ctrl+X", "Edit/Cut"));
	AddCommand(KeyCommand(AKKeys::EDIT_COPY, "Ctrl+C", "Edit/Copy"));
	AddCommand(KeyCommand(AKKeys::EDIT_PASTE, "Ctrl+V", "Edit/Paste"));
	AddCommand(KeyCommand(AKKeys::EDIT_DELETE, "Del", "Edit/Delete"));
	
	// Transport
	AddCommand(KeyCommand(AKKeys::TRANSPORT_PLAY, "Space", "Transport/Play"));
	AddCommand(KeyCommand(AKKeys::TRANSPORT_STOP, "Ctrl+Space", "Transport/Stop"));
	AddCommand(KeyCommand(AKKeys::TRANSPORT_RECORD, "R", "Transport/Record"));
	
	// Audio
	AddCommand(KeyCommand(AKKeys::AUDIO_NORMALIZE, "", "Audio/Normalize"));
	AddCommand(KeyCommand(AKKeys::AUDIO_GAIN, "", "Audio/Gain"));
	
	// MIDI
	AddCommand(KeyCommand(AKKeys::MIDI_QUANTIZE, "", "MIDI/Quantize"));
	AddCommand(KeyCommand(AKKeys::MIDI_TRANSPOSE, "", "MIDI/Transpose"));
	
	// Additional commands
	AddCommand(KeyCommand(AKKeys::PREFERENCES_OPEN, "Ctrl+,", "File/Preferences..."));
	AddCommand(KeyCommand(AKKeys::PROJECT_SETUP, "", "Project/Project Setup..."));
	AddCommand(KeyCommand(AKKeys::MEDIA_OPEN_POOL, "", "Media/Open Pool Window"));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_OPEN, "", "File/Key Commands..."));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_SAVE_PRESET, "", "Key Commands/Save Preset"));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_LOAD_PRESET, "", "Key Commands/Load Preset"));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_DELETE_PRESET, "", "Key Commands/Delete Preset"));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_RESET_ALL, "", "Key Commands/Reset All"));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_SHOW_MACROS, "", "Key Commands/Show Macros"));
	
	// Preferences dialog sections
	AddCommand(KeyCommand(AKKeys::PREFS_APPEARANCE, "", "Preferences/Appearance"));
	AddCommand(KeyCommand(AKKeys::PREFS_AUDIO, "", "Preferences/Audio"));
	AddCommand(KeyCommand(AKKeys::PREFS_MIDI, "", "Preferences/MIDI"));
	AddCommand(KeyCommand(AKKeys::PREFS_DEVICES, "", "Preferences/Devices"));
	AddCommand(KeyCommand(AKKeys::PREFS_TRANSPORT, "", "Preferences/Transport"));
	AddCommand(KeyCommand(AKKeys::PREFS_EDITING, "", "Preferences/Editing"));
	AddCommand(KeyCommand(AKKeys::PREFS_KEY_COMMANDS, "", "Preferences/Key Commands"));
	AddCommand(KeyCommand(AKKeys::PREFS_PLUGINS, "", "Preferences/Plugins"));
	
	// Key Commands dialog specific commands
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_ASSIGN, "", "Key Commands/Assign"));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_DELETE, "", "Key Commands/Delete"));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_REFRESH, "", "Key Commands/Refresh"));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_SEARCH, "", "Key Commands/Search"));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_RESET_SELECTED, "", "Key Commands/Reset Selected"));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_IMPORT, "", "Key Commands/Import"));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_EXPORT, "", "Key Commands/Export"));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_COLLISION_SELECT, "", "Key Commands/Select Collision"));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_OPEN_PRESET, "", "Key Commands/Open Preset"));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_SAVE_PRESET_AS, "", "Key Commands/Save Preset As"));
	
	// Macro related commands
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_NEW_MACRO, "", "Key Commands/New Macro"));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_EDIT_MACRO, "", "Key Commands/Edit Macro"));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_DELETE_MACRO, "", "Key Commands/Delete Macro"));
	AddCommand(KeyCommand(AKKeys::KEY_COMMANDS_ADD_COMMAND_TO_MACRO, "", "Key Commands/Add Command to Macro"));

	// Preferences dialog commands
	AddCommand(KeyCommand(AKKeys::PREFERENCES_REFRESH, "", "Preferences/Refresh"));
	AddCommand(KeyCommand(AKKeys::PREFERENCES_APPLY, "", "Preferences/Apply"));
	AddCommand(KeyCommand(AKKeys::PREFERENCES_RESET, "", "Preferences/Reset"));
	AddCommand(KeyCommand(AKKeys::PREFERENCES_SAVE_PRESET, "", "Preferences/Save Preset"));
	AddCommand(KeyCommand(AKKeys::PREFERENCES_LOAD_PRESET, "", "Preferences/Load Preset"));
	AddCommand(KeyCommand(AKKeys::PREFERENCES_DELETE_PRESET, "", "Preferences/Delete Preset"));
	AddCommand(KeyCommand(AKKeys::PREFERENCES_RENAME_PRESET, "", "Preferences/Rename Preset"));
	AddCommand(KeyCommand(AKKeys::PREFERENCES_MARKED_ONLY, "", "Preferences/Store Marked Only"));
	AddCommand(KeyCommand(AKKeys::PREFERENCES_DEFAULTS, "", "Preferences/Restore Defaults"));
	AddCommand(KeyCommand(AKKeys::PREFERENCES_HELP, "", "Preferences/Help"));
}

void KeyCommands::SaveCommands() {
	LOG("Saving key commands");
	// Stub - implement actual command saving
}

void KeyCommands::AddCommand(const KeyCommand& cmd) {
	// Check if command already exists and update it if so
	for(int i = 0; i < commands.GetCount(); i++) {
		if(commands[i].command_id == cmd.command_id) {
			commands[i] = cmd;
			return;
		}
	}
	// If command doesn't exist, add it as new
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
	// Using the AK key system, we could potentially get the readable name from the key ID
	// For now, we'll iterate through our commands to find the matching ID
	for(const KeyCommand& cmd : commands) {
		if(cmd.command_id == key_id) {
			return cmd.description;
		}
	}
	return "Unknown Command";
}

int KeyCommands::GetKeyId(const Upp::String& key_name) const {
	// Find the command by description and return its ID
	for(const KeyCommand& cmd : commands) {
		if(cmd.description == key_name) {
			return cmd.command_id;
		}
	}
	return -1; // Not found
}

}