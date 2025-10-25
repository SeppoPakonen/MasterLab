#include "ProjectMgmt.h"
namespace am {

void History::Undo() {
	if (pos > 0) {
		pos--;
		if (stack[pos].undo_action) {
			stack[pos].undo_action();
		}
	}
}

void History::Redo() {
	if (pos < (int)stack.GetCount()) {
		if (stack[pos].redo_action) {
			stack[pos].redo_action();
		}
		pos++;
	}
}

void History::Push(const Operation& op) {
	// Remove any redo operations if we're not at the end
	while (stack.GetCount() > pos) {
		stack.RemoveLast();
	}
	
	stack.Add(op);
	pos++;
}

Vector<String> History::GetStack() const {
	Vector<String> result;
	for (const auto& op : stack) {
		result.Add(op.description);
	}
	return result;
}

void History::Clear() {
	stack.Clear();
	pos = 0;
}

}