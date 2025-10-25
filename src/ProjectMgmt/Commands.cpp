#include "ProjectMgmt.h"
namespace am {

void CommandManager::Execute(int id, const CommandContext& ctx) {
	if (command_map.Find(id) >= 0) {
		command_map[id](ctx);
	}
}

void CommandManager::RegisterCommand(int id, std::function<void(const CommandContext&)> func) {
	command_map.GetAdd(id) = func;
	enabled_state.GetAdd(id) = true;  // Default to enabled
	toggle_state.GetAdd(id) = false;  // Default to not toggled
}

bool CommandManager::IsCommandEnabled(int id) const {
	return enabled_state.Get(id, true);
}

bool CommandManager::IsCommandToggled(int id) const {
	return toggle_state.Get(id, false);
}

}