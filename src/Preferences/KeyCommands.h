#ifndef _Preferences_KeyCommands_h_
#define _Preferences_KeyCommands_h_

#include <CtrlLib/CtrlLib.h>
#include <ProjectMgmt/ProjectMgmt.h>  // Include the project management module
using namespace Upp;

namespace am {

struct KeyCommand {
	int command_id;
	String key_sequence;
	String description;
};

class KeyCommands {
public:
	KeyCommands();
	void LoadCommands();
	void SaveCommands();
	Vector<KeyCommand> GetCommands() const { return commands; }
	void AddCommand(const KeyCommand& cmd);
	void RemoveCommand(int commandId);
	void UpdateCommand(int commandId, const String& newKeySequence);
	
	// New methods to work with U++ keys
	String GetKeyName(int key_id) const;
	int GetKeyId(const String& key_name) const;
	
private:
	Vector<KeyCommand> commands;
};

}

#endif