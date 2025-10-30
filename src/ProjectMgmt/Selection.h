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
	const Upp::Vector<Value>& GetSelected() const { return selected_items; }
	bool IsSelected(Value item) const { 
		for(int i = 0; i < selected_items.GetCount(); i++) {
			if(selected_items[i] == item) return true;
		}
		return false; 
	}
	bool IsEmpty() const { return selected_items.IsEmpty(); }
	int GetCount() const { return selected_items.GetCount(); }
	
	// Operations
	void SelectAll();
	void Invert();
	void CopyToClipboard();
	void PasteFromClipboard();
	
private:
	Upp::Vector<Value> selected_items;
};

}

#endif