/*
SPDX-FileCopyrightText: 2012 Till Theato <root@ttill.de>
SPDX-FileCopyrightText: 2014 Jean-Baptiste Mardelle <jb@kdenlive.org>
U++ Conversion: 2026 MasterLab Team
*/

#include "Bin.h"
#include "../Core.h"
#include "../Mainwindow.h"
#include "Projectitemmodel.h"

NAMESPACE_UPP

// --- BinTreeCtrl ---

BinTreeCtrl::BinTreeCtrl() {
    // Basic U++ TreeCtrl setup
}

void BinTreeCtrl::LeftDown(Point p, dword flags) {
    TreeCtrl::LeftDown(p, flags);
}

void BinTreeCtrl::RightDown(Point p, dword flags) {
    TreeCtrl::RightDown(p, flags);
}

void BinTreeCtrl::DragAndDrop(Point p, PasteClip& d) {
    // Implement U++ drag and drop logic
}

// --- Bin ---

Bin::Bin() {
    is_main_bin = true;
    is_loading = false;
    view_type = TREE_VIEW;

    Add(tree_view.SizePos());
    
    // Add toolbar at the top
    AddFrame(tool_bar);
    tool_bar.Set(THISBACK(SetupToolbar));
}

Bin::~Bin() {
}

const String Bin::SetDocument(CoolDoc* project, const String& id) {
    // TODO: U++ Migration - Link ProjectItemModel
    return "";
}

void Bin::CleanDocument() {
}

void Bin::CreateClip(const XmlElement& xml) {
    // TODO: Parse MLT XML and add to model
}

std::shared_ptr<ProjectClip> Bin::GetBinClip(const String& id) {
    return nullptr;
}

size_t Bin::GetClipDuration(int item_id) const {
    return 0;
}

Size Bin::GetFrameSize(int item_id) const {
    return Size(1920, 1080);
}

void Bin::RefreshClip(const String& id) {
    tree_view.Refresh();
}

void Bin::ReloadClip(const String& id) {
}

void Bin::SelectClipById(const String& id, int frame, Point zone, bool activate_monitor) {
    // TODO: Locate item in model and select in tree_view
}

void Bin::Layout() {
    // Handle specific layout needs beyond SizePos
}

void Bin::Paint(Draw& draw) {
    Size sz = GetSize();
    if (tree_view.GetChildCount(0) == 0) {
        // Draw the "Drop files to import" placeholder
        String msg = "Double click or drop files to import media";
        Font font = StdFont().Bold().Height(20);
        Size msg_sz = GetTextSize(msg, font);
        draw.DrawText((sz.cx - msg_sz.cx) / 2, (sz.cy - msg_sz.cy) / 2, msg, font, SColorDisabled());
    }
}

void Bin::SetupToolbar(Bar& bar) {
    bar.Add("Add Clip", CtrlImg::plus(), THISBACK(OnSearch)); // Placeholder
    bar.Separator();
    bar.Add(search_line.Width(150));
    search_line.WhenAction = THISBACK(OnSearch);
}

void Bin::OnSearch() {
    String text = search_line.GetText();
    // TODO: Filter tree_view model
}

END_UPP_NAMESPACE
