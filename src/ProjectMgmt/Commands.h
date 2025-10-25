#ifndef _ProjectMgmt_Commands_h_
#define _ProjectMgmt_Commands_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {
	
enum CommandID {
	CMD_FILE_NEW_PROJECT,
	CMD_FILE_OPEN,
	CMD_FILE_SAVE,
	CMD_FILE_SAVE_AS,
	CMD_FILE_CLOSE,
	CMD_EDIT_UNDO,
	CMD_EDIT_REDO,
	CMD_EDIT_CUT,
	CMD_EDIT_COPY,
	CMD_EDIT_PASTE,
	CMD_EDIT_DELETE,
	CMD_TRANSPORT_PLAY,
	CMD_TRANSPORT_STOP,
	CMD_TRANSPORT_RECORD,
	CMD_AUDIO_NORMALIZE,
	CMD_AUDIO_GAIN,
	CMD_MIDI_QUANTIZE,
	CMD_MIDI_TRANSPOSE,
	// Add more command IDs as needed
};

struct CommandContext {
	// Context information for command execution
	ValueMap params;
};

class CommandManager {
public:
	void Execute(CommandID id, const CommandContext& ctx = CommandContext());
	void RegisterCommand(CommandID id, std::function<void(const CommandContext&)> func);
	bool IsCommandEnabled(CommandID id) const;
	bool IsCommandToggled(CommandID id) const;
private:
	HashMap<CommandID, std::function<void(const CommandContext&)>> command_map;
	HashMap<CommandID, bool> enabled_state;
	HashMap<CommandID, bool> toggle_state;
};

}

#endif