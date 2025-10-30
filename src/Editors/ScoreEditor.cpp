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
	ActiveFocus(*this);
}

void ScoreEditor::Close() {
	// Close the editor
	Close();
}

void ScoreEditor::SetData(void* data) {
	// Set the data for the editor
}

}