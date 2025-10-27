#include "Browser.h"
namespace am {

MediaBay::MediaBay() {
	Init();
}

void MediaBay::Init() {
	Title("Media Bay");
	Size(600, 400);
	
	// Initialize UI elements
}

void MediaBay::Open() {
	// Open the window
	ActiveFocus(*this);
}

void MediaBay::Close() {
	// Close the window
	Break();
}

void MediaBay::Refresh() {
	// Refresh the display
}

}