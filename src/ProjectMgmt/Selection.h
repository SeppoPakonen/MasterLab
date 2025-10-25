#ifndef _ProjectMgmt_Selection_h_
#define _ProjectMgmt_Selection_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class Selection {
public:
	// Basic selection operations
	void Clear();
	void Select(Value item);
	void Deselect(Value item);
	void Toggle(Value item);
	
	// Get selection
	Vector<Value> GetSelected() const { return selected_items; }
	bool IsSelected(Value item) const { return selected_items.Find(item) >= 0; }
	bool IsEmpty() const { return selected_items.IsEmpty(); }
	int GetCount() const { return selected_items.GetCount(); }
	
	// Operations
	void SelectAll();
	void Invert();
	void CopyToClipboard();
	void PasteFromClipboard();
	
private:
	Vector<Value> selected_items;
};

}

#endif