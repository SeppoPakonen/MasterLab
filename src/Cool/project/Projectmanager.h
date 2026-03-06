/*
SPDX-FileCopyrightText: 2014 Till Theato <root@ttill.de>
SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_ProjectManager_h_
#define _Cool_ProjectManager_h_

#include <Core/Core.h>
#include "../Definitions.h"

NAMESPACE_UPP

// Forward declarations
class CoolDoc;
class TimelineItemModel;
class DocUndoStack;
class MarkerListModel;

class ProjectManager {
public:
    ProjectManager(Core* core);
    virtual ~ProjectManager();

    // Document access
    virtual CoolDoc* GetCurrentDoc() { return project; }
    
    // Lifecycle
    void Init(const String& project_url, const Vector<String>& clip_list);
    void NewFile(const String& profile_name, bool show_settings = true);
    void OpenFile(const String& url);
    bool SaveFile();
    bool SaveFileAs(const String& output_file_name);
    bool CloseCurrentDocument(bool save_changes = true);

    // Timeline management
    std::shared_ptr<TimelineItemModel> GetTimeline();
    void SetActiveTimeline(const String& uuid);
    int  GetTimelinesCount() const;
    
    // Undostack access
    virtual std::shared_ptr<DocUndoStack> GetUndoStack();
    
    // Logic
    void PrepareSave();
    void SyncTimeline(const String& uuid, bool refresh = false);
    
    // Accessors
    // KRecentFilesAction *recentFilesAction(); // TODO: U++ Recent Files logic

private:
    Core* core_instance;
    CoolDoc* project = nullptr;
    
    std::shared_ptr<TimelineItemModel> active_timeline_model;
    
    String start_url;
    Vector<String> load_clips_on_open;
    
    // Internal helpers
    bool CheckForBackupFile(const String& url);
    void FinalizeDocumentOpening(CoolDoc* document);
    void AbortProjectLoad(const String& url);
};

END_UPP_NAMESPACE

#endif
