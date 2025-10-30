#include "Editors.h"
namespace am {

ListEditor::ListEditor() {
	Init();
}

void ListEditor::Init() {
	Title("List Editor");
	Size(800, 600);
	
	// Initialize UI elements
}

void ListEditor::Open() {
	// Open the editor
	ActiveFocus(*this);
}

void ListEditor::Close() {
	// Close the editor
	Close();
}

void ListEditor::SetData(void* data) {
	// Set the data for the editor
}

}