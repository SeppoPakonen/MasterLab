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
	
	CommandContext() {}
	
	// Copy constructor
	CommandContext(const CommandContext& other) = default;
	
	// Move constructor
	CommandContext(CommandContext&& other) = default;
	
	// Assignment operators
	CommandContext& operator=(const CommandContext& other) = default;
	CommandContext& operator=(CommandContext&& other) = default;
};

// Define a U++ compatible function type (using callback via Event)
typedef Function<void(const CommandContext&)> CommandFunction;

class CommandManager {
public:
	void Execute(int id, const CommandContext& ctx = CommandContext());
	void RegisterCommand(int id, CommandFunction func);
	bool IsCommandEnabled(int id) const;
	bool IsCommandToggled(int id) const;
private:
	VectorMap<int, CommandFunction> command_map;
	VectorMap<int, bool> enabled_state;
	VectorMap<int, bool> toggle_state;
};

}

// For CommandContext which doesn't need U++ deep copy trait since it's not stored in Upp::Vector
// but for VectorMap storage we may need to handle the command_map differently
// Since the error is about std::function in Vector, we need to address that

#endif