#include "ProjectMgmt.h"
namespace am {

void CommandManager::Execute(CommandID id, const CommandContext& ctx) {
	if (command_map.Find(id) >= 0) {
		command_map[id](ctx);
	}
}

void CommandManager::RegisterCommand(CommandID id, std::function<void(const CommandContext&)> func) {
	command_map.GetAdd(id) = func;
	enabled_state.GetAdd(id) = true;  // Default to enabled
	toggle_state.GetAdd(id) = false;  // Default to not toggled
}

bool CommandManager::IsCommandEnabled(CommandID id) const {
	return enabled_state.Get(id, true);
}

bool CommandManager::IsCommandToggled(CommandID id) const {
	return toggle_state.Get(id, false);
}

}