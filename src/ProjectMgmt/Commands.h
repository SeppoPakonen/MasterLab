#ifndef _ProjectMgmt_Commands_h_
#define _ProjectMgmt_Commands_h_

#include <Core/Core.h>
using namespace Upp;

// Include the key definitions
#define KEYGROUPNAME "AK"
#define KEYNAMESPACE AKKeys
#define KEYFILE      <ProjectMgmt/AK.key>
#include             <CtrlLib/key_source.h>

namespace am {

struct CommandContext {
	// Context information for command execution
	ValueMap params;
};

class CommandManager {
public:
	void Execute(int id, const CommandContext& ctx = CommandContext());
	void RegisterCommand(int id, std::function<void(const CommandContext&)> func);
	bool IsCommandEnabled(int id) const;
	bool IsCommandToggled(int id) const;
private:
	HashMap<int, std::function<void(const CommandContext&)>> command_map;
	HashMap<int, bool> enabled_state;
	HashMap<int, bool> toggle_state;
};

}

#endif