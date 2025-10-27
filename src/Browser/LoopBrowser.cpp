#include "Browser.h"
namespace am {

LoopBrowser::LoopBrowser() {
	Init();
}

void LoopBrowser::Init() {
	Title("Loop Browser");
	Size(600, 400);
	
	// Initialize UI elements
}

void LoopBrowser::Open() {
	// Open the window
	ActiveFocus(*this);
}

void LoopBrowser::Close() {
	// Close the window
	Break();
}

void LoopBrowser::Refresh() {
	// Refresh the display
}

}