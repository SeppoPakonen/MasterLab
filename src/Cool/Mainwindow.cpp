/*
    SPDX-FileCopyrightText: 2007 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#include "Mainwindow.h"
#include "Core.h"
#include "monitor/Monitor.h"
#include "timeline2/view/Timelinetabs.hpp"
#include "bin/Bin.h"
#include "assets/Assetpanel.hpp"

NAMESPACE_UPP

VectorMap<String, Image> MainWindow::luma_cache;
VectorMap<String, Vector<String>> MainWindow::luma_files;

MainWindow::MainWindow() {
	Title("Cool - MasterLab Video Editor");
	SetRect(0, 0, 1024, 768);
	
	AddFrame(menu_bar);
	AddFrame(tool_bar);
	AddFrame(status_bar);
	
	// Main UI structure
	Add(main_tabs.SizePos());
	
	SetupActions();
}

MainWindow::~MainWindow() {
}

void MainWindow::Init() {
	// Initialize core components
	clip_monitor = new Monitor();
	project_monitor = new Monitor();
	timeline_tabs = new TimelineTabs();
	
	// Build layout (Placeholder for U++ Frame/Splitter setup)
	// In U++, we typically use Splitters for dock-like behavior
	
	// Create main bin if not already existing
	if (bin_widgets.IsEmpty()) {
		Bin* main_bin = new Bin();
		AddBin(main_bin, "Project Bin");
	}
}

void MainWindow::SetupActions() {
	menu_bar.Set(THISBACK(SetupMenu));
	tool_bar.Set(THISBACK(SetupToolbar));
}

void MainWindow::SetupMenu(Bar& bar) {
	bar.Add("File", [=](Bar& bar) {
		bar.Add("New", THISBACK(Init)); // Placeholder
		bar.Separator();
		bar.Add("Exit", THISBACK(Close));
	});
}

void MainWindow::SetupToolbar(Bar& bar) {
	bar.Add("New", CtrlImg::File(), THISBACK(Init));
}

void MainWindow::Layout() {
	// Custom layout logic if not using SizePos()
}

bool MainWindow::Key(dword key, int count) {
	if (key == K_ESCAPE) {
		// Focus management
		return true;
	}
	return TopWindow::Key(key, count);
}

void MainWindow::Close() {
	// Cleanup and save options
	TopWindow::Close();
}

TimelineWidget* MainWindow::GetCurrentTimeline() const {
	// TODO: U++ Migration - Access from timeline_tabs
	return nullptr;
}

Bin* MainWindow::GetBin() {
	return bin_widgets.IsEmpty() ? nullptr : bin_widgets[0];
}

Bin* MainWindow::ActiveBin() {
	// TODO: Find focused bin
	return GetBin();
}

void MainWindow::AddBin(Bin* bin, const String& bin_name, bool update_count) {
	bin_widgets.Add(bin);
	// Add to UI area
}

void MainWindow::DisplayMessage(const String& message, int message_type, int timeout) {
	status_bar.Set(message);
}

END_UPP_NAMESPACE
