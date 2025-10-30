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
	ActiveFocus(*this);
}

void KeyEditor::Close() {
	// Close the editor
	Close();
}

void KeyEditor::SetData(void* data) {
	// Set the data for the editor
}

}