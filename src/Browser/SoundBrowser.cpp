#include "Browser.h"
namespace am {

SoundBrowser::SoundBrowser() {
	Init();
}

void SoundBrowser::Init() {
	Title("Sound Browser");
	Size(600, 400);
	
	// Initialize UI elements
}

void SoundBrowser::Open() {
	// Open the window
	ActiveFocus(*this);
}

void SoundBrowser::Close() {
	// Close the window
	Break();
}

void SoundBrowser::Refresh() {
	// Refresh the display
}

}