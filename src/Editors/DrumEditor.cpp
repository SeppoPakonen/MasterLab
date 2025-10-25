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
	ActiveFocus();
}

void DrumEditor::Close() {
	// Close the editor
	CloseWindow();
}

void DrumEditor::SetData(void* data) {
	// Set the data for the editor
}

}