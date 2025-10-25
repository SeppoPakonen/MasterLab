#include "Preferences.h"
namespace am {

KeyCommands::KeyCommands() {
	// Initialize key command system
}

void KeyCommands::LoadCommands() {
	LOG("Loading key commands");
	// Stub - implement actual command loading
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

}