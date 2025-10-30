#ifndef _ProjectMgmt_History_h_
#define _ProjectMgmt_History_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct Operation : public Upp::Moveable<Operation> {
	Upp::String description;
	std::function<void()> undo_action;
	std::function<void()> redo_action;
	
	Operation() {}
	Operation(const Upp::String& desc, std::function<void()> undo_func, std::function<void()> redo_func)
		: description(desc), undo_action(undo_func), redo_action(redo_func) {}
	
	// Copy constructor
	Operation(const Operation& other) = default;
	
	// Move constructor
	Operation(Operation&& other) = default;
	
	// Assignment operators
	Operation& operator=(const Operation& other) = default;
	Operation& operator=(Operation&& other) = default;
};

class History {
public:
	void Undo();
	void Redo();
	void Push(const Operation& op);
	bool CanUndo() const { return pos > 0; }
	bool CanRedo() const { return pos < (int)stack.GetCount(); }
	Upp::Vector<Upp::String> GetStack() const;
	int GetPosition() const { return pos; }
	void Clear();
private:
	Upp::Vector<Operation> stack;
	int pos = 0;  // Points to next operation to redo
};

}

#endif