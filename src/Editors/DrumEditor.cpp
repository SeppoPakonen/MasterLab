#include "Editors.h"
namespace am {

DrumEditor::DrumEditor() {
	Init();
}

void DrumEditor::Init() {
	Title("Drum Editor");
	Size(800, 600);
	
	// Initialize UI elements
}

void DrumEditor::Open() {
	// Open the editor
	ActiveFocus(*this);
}

void DrumEditor::Close() {
	// Close the editor
	Close();
}

void DrumEditor::SetData(void* data) {
	// Set the data for the editor
}

}