#ifndef _Preferences_KeyCommands_h_
#define _Preferences_KeyCommands_h_

#include <CtrlLib/CtrlLib.h>
#include <ProjectMgmt/ProjectMgmt.h>  // Include the project management module
using namespace Upp;

namespace am {

struct KeyCommand : public Moveable<KeyCommand> {
	int command_id;
	Upp::String key_sequence;
	Upp::String description;
	
	// Add explicit constructor
	KeyCommand() = default;
	KeyCommand(int id, const Upp::String& sequence, const Upp::String& desc) 
		: command_id(id), key_sequence(sequence), description(desc) {}
	
	// Add explicit copy constructor and assignment operator
	KeyCommand(const KeyCommand& other) 
		: command_id(other.command_id), 
		  key_sequence(other.key_sequence), 
		  description(other.description) {}
	
	KeyCommand& operator=(const KeyCommand& other) {
		if(this != &other) {
			command_id = other.command_id;
			key_sequence = other.key_sequence;
			description = other.description;
		}
		return *this;
	}
};

class KeyCommands {
public:
	KeyCommands();
	void LoadCommands();
	void SaveCommands();
	const Upp::Vector<KeyCommand>& GetCommands() const { return commands; }
	void AddCommand(const KeyCommand& cmd);
	void RemoveCommand(int commandId);
	void UpdateCommand(int commandId, const Upp::String& newKeySequence);
	
	// New methods to work with U++ keys
	Upp::String GetKeyName(int key_id) const;
	int GetKeyId(const Upp::String& key_name) const;
	
private:
	Upp::Vector<KeyCommand> commands;
};

}

#endif