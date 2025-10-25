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
	ActiveFocus();
}

void ListEditor::Close() {
	// Close the editor
	CloseWindow();
}

void ListEditor::SetData(void* data) {
	// Set the data for the editor
}

}