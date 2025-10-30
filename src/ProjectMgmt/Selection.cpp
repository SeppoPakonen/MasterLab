#include "ProjectMgmt.h"
namespace am {

void Selection::Clear() {
	selected_items.Clear();
}

void Selection::Select(Value item) {
	if (!IsSelected(item)) {
		selected_items.Add(item);
	}
}

void Selection::Deselect(Value item) {
	int pos = -1;
	for(int i = 0; i < selected_items.GetCount(); i++) {
		if(selected_items[i] == item) {
			pos = i;
			break;
		}
	}
	if (pos >= 0) {
		selected_items.Remove(pos);
	}
}

void Selection::Toggle(Value item) {
	if (IsSelected(item)) {
		Deselect(item);
	} else {
		Select(item);
	}
}

void Selection::SelectAll() {
	// This would be implemented based on the context of what can be selected
	// For now it's a stub
}

void Selection::Invert() {
	// This would be implemented based on the context of what can be selected
	// For now it's a stub
}

void Selection::CopyToClipboard() {
	// This would interface with the system clipboard
	// For now it's a stub
}

void Selection::PasteFromClipboard() {
	// This would interface with the system clipboard
	// For now it's a stub
}

}