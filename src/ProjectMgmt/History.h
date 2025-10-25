#ifndef _ProjectMgmt_History_h_
#define _ProjectMgmt_History_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct Operation {
	String description;
	std::function<void()> undo_action;
	std::function<void()> redo_action;
};

class History {
public:
	void Undo();
	void Redo();
	void Push(const Operation& op);
	bool CanUndo() const { return pos > 0; }
	bool CanRedo() const { return pos < (int)stack.GetCount(); }
	Vector<String> GetStack() const;
	int GetPosition() const { return pos; }
	void Clear();
private:
	Vector<Operation> stack;
	int pos = 0;  // Points to next operation to redo
};

}

#endif