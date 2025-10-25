#include "MediaPool.h"
namespace am {

PoolWindow::PoolWindow() {
	Init();
}

void PoolWindow::Init() {
	Title("Media Pool");
	Size(800, 600);
	
	// Initialize UI elements
}

void PoolWindow::Open() {
	// Open the window
	ActiveFocus();
}

void PoolWindow::Close() {
	// Close the window
	CloseWindow();
}

void PoolWindow::Refresh() {
	// Refresh the display
}

}