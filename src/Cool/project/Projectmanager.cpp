/*
SPDX-FileCopyrightText: 2014 Till Theato <root@ttill.de>
SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
U++ Conversion: 2026 MasterLab Team
*/

#include "Projectmanager.h"
#include "../Core.h"
#include "../Mainwindow.h"
#include "../doc/Kdenlivedoc.h"
#include "../timeline2/model/Timelineitemmodel.hpp"

NAMESPACE_UPP

ProjectManager::ProjectManager(Core* core)
    : core_instance(core)
{
    // Ensure default directories exist using U++ RealizeDirectory
    String data_path = ConfigFile("");
    RealizeDirectory(AppendFileName(data_path, ".backup"));
    RealizeDirectory(AppendFileName(data_path, "titles"));
}

ProjectManager::~ProjectManager() {
    if (project) delete project;
}

void ProjectManager::Init(const String& project_url, const Vector<String>& clip_list) {
    start_url = project_url;
    load_clips_on_open <<= clip_list;
    
    // TODO: Setup U++ Project Actions (Undo, Redo, Save, etc)
}

void ProjectManager::NewFile(const String& profile_name, bool show_settings) {
    if (project) {
        if (!CloseCurrentDocument()) return;
    }
    
    // TODO: U++ Migration - Implement ProjectSettings dialog and KdenliveDoc construction
    Cout() << "Creating new project with profile: " << profile_name << EOL;
}

void ProjectManager::OpenFile(const String& url) {
    // TODO: U++ Migration - Implement file loading and XML parsing
}

bool ProjectManager::SaveFile() {
    if (!project) return false;
    // TODO: Implement XML serialization
    return true;
}

bool ProjectManager::SaveFileAs(const String& output_file_name) {
    // TODO: Implement Save As logic
    return true;
}

bool ProjectManager::CloseCurrentDocument(bool save_changes) {
    if (project && project->IsModified() && save_changes) {
        // TODO: Ask user via PromptYesNo
    }
    
    if (project) {
        delete project;
        project = nullptr;
    }
    
    return true;
}

std::shared_ptr<TimelineItemModel> ProjectManager::GetTimeline() {
    return active_timeline_model;
}

void ProjectManager::SetActiveTimeline(const String& uuid) {
    if (!project) return;
    // active_timeline_model = project->GetTimeline(uuid);
}

int ProjectManager::GetTimelinesCount() const {
    // if (!project) return 0;
    return 1; // Placeholder
}

std::shared_ptr<DocUndoStack> ProjectManager::GetUndoStack() {
    // if (project) return project->GetUndoStack();
    return nullptr;
}

void ProjectManager::PrepareSave() {
    if (project) {
        // project->PrepareSave();
    }
}

void ProjectManager::SyncTimeline(const String& uuid, bool refresh) {
    // TODO: Sync model with MLT producer
}

bool ProjectManager::CheckForBackupFile(const String& url) {
    // TODO: Check for crash recovery files
    return false;
}

void ProjectManager::FinalizeDocumentOpening(CoolDoc* document) {
    // TODO: Link monitors and UI components
}

void ProjectManager::AbortProjectLoad(const String& url) {
    // Cleanup state
}

END_UPP_NAMESPACE
