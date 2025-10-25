#ifndef _Preferences_KeyCommands_h_
#define _Preferences_KeyCommands_h_

#include <CtrlLib/CtrlLib.h>
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
	
private:
	Vector<KeyCommand> commands;
};

}

#endif