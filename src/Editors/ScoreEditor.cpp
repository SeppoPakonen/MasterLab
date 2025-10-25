#include "Editors.h"
namespace am {

ScoreEditor::ScoreEditor() {
	Init();
}

void ScoreEditor::Init() {
	Title("Score Editor");
	Size(800, 600);
	
	// Initialize UI elements
}

void ScoreEditor::Open() {
	// Open the editor
	ActiveFocus();
}

void ScoreEditor::Close() {
	// Close the editor
	CloseWindow();
}

void ScoreEditor::SetData(void* data) {
	// Set the data for the editor
}

}