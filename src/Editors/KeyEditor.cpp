#include "Editors.h"
namespace am {

KeyEditor::KeyEditor() {
	Init();
}

void KeyEditor::Init() {
	Title("Key Editor");
	Size(800, 600);
	
	// Initialize UI elements
}

void KeyEditor::Open() {
	// Open the editor
	ActiveFocus();
}

void KeyEditor::Close() {
	// Close the editor
	CloseWindow();
}

void KeyEditor::SetData(void* data) {
	// Set the data for the editor
}

}