#include "Editors.h"
namespace am {

InPlaceEditor::InPlaceEditor() {
	Init();
}

void InPlaceEditor::Init() {
	Title("In-Place Editor");
	Size(800, 600);
	
	// Initialize UI elements
}

void InPlaceEditor::Open() {
	// Open the editor
	ActiveFocus(*this);
}

void InPlaceEditor::Close() {
	// Close the editor
	Close();
}

void InPlaceEditor::SetData(void* data) {
	// Set the data for the editor
}

}