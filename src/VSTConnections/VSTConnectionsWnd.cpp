#include "VSTConnectionsWnd.h"

NAMESPACE_UPP

VSTConnectionsWnd::VSTConnectionsWnd() {
	// Initialize the presenter with the control and service
	presenter = new VSTConnections::VSTConnectionsPresenter(connectionsCtrl, ioMatrixService);
	
	// Add the main control to the window
	AddFrame(toolBar);
	Add(connectionsCtrl);
	
	// Connect the presenter to the view
	presenter->ConnectView();
	
	// Create the menu bar and toolbar
	CreateMenuBar();
	CreateToolBar();
	
	// Set window title
	Title("VST Connections");
	
	// Initialize with default data
	Data();
}

void VSTConnectionsWnd::Open() {
	// Open the VST Connections window
}

void VSTConnectionsWnd::Close() {
	// Clean up and close the window
	if (presenter) {
		delete presenter;
		presenter = nullptr;
	}
}

void VSTConnectionsWnd::CreateMenuBar() {
	// Create menu bar for the window
	MenuBar menubar;
	
	menubar.Add("File.New", CtrlImg::newb(), THISBACK(New));
	menubar.Add("File.Open", CtrlImg::open(), THISBACK(OpenFile));
	menubar.Add("File.Save", CtrlImg::save(), THISBACK(Save));
	menubar.Add("File.Save As...", THISBACK(SaveAs));
	menubar.Add("File.Close", THISBACK(CloseWindow));
	
	menubar.Add("Edit.Undo", CtrlImg::undo(), THISBACK(Data));
	menubar.Add("Edit.Redo", CtrlImg::redo(), THISBACK(Data));
	
	menubar.Add("View.Refresh", CtrlImg::refresh(), THISBACK(Data));
	
	SetMenuBar(menubar);
}

void VSTConnectionsWnd::CreateToolBar() {
	// Create toolbar for the window
	toolBar.SetImage(CtrlImg::application());
	toolBar.Add("New", CtrlImg::newb(), THISBACK(New));
	toolBar.Add("Open", CtrlImg::open(), THISBACK(OpenFile));
	toolBar.Add("Save", CtrlImg::save(), THISBACK(Save));
	toolBar.Add("Refresh", CtrlImg::refresh(), THISBACK(Data));
	toolBar.Add("Apply", CtrlImg::ok(), THISBACK2(presenter->ApplyChanges));
}

void VSTConnectionsWnd::Data() {
	// Load or refresh data in the UI
	if (presenter) {
		presenter->LoadConnections();
	}
}

void VSTConnectionsWnd::New() {
	// Handle new connection setup
	PromptOK("New connection setup functionality would be implemented here.");
}

void VSTConnectionsWnd::OpenFile() {
	// Handle opening connection presets
	PromptOK("Open connection preset functionality would be implemented here.");
}

void VSTConnectionsWnd::Save() {
	// Handle saving connections
	if (presenter) {
		presenter->SaveConnections();
	}
	PromptOK("Connections saved successfully.");
}

void VSTConnectionsWnd::SaveAs() {
	// Handle saving connections as preset
	PromptOK("Save As connection preset functionality would be implemented here.");
}

void VSTConnectionsWnd::CloseWindow() {
	// Close the window
	Close();
}

END_UPP_NAMESPACE