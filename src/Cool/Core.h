/*
SPDX-FileCopyrightText: 2014 Till Theato <root@ttill.de>
SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_Core_h_
#define _Cool_Core_h_

#include "Cool.h"
#include "Definitions.h"
#include "jobs/Taskmanager.h"
#include "layouts/Layoutinfo.h"
#include "Undohelper.hpp"
#include "utils/Timecode.h"

// Forward declarations for U++ converted classes
class Bin;
class DocUndoStack;
class EffectStackModel;
class CoolDoc; 
class LibraryWidget;
class MainWindow;
class MediaCapture;
class MediaBrowser;
class MixerManager;
class Monitor;
class MonitorManager;
class ProfileModel;
class ProjectItemModel;
class ProjectManager;
class Splash;
class SubtitleEdit;
class SubtitleModel;
class TextBasedEdit;
class GuidesList;
class KeyframeModelList;
class TimeRemap;

namespace Mlt {
    class Repository;
    class Producer;
    class Profile;
}

NAMESPACE_UPP

#undef pCore
#define pCore Core::Self()

class Core {
public:
    friend class CoolDoc;
    friend class ProjectManager;

    // Singleton management
    static Core& Self();
    static void  Clean();
    static bool  Build(int package_type, bool test_mode = false, bool debug_mode = false, bool show_welcome = true);

    Core(const Core&) = delete;
    Core& operator=(const Core&) = delete;

    // State members
    Mutex           xml_mutex;
    bool            is_closing = false;
    String          last_active_bin;
    bool            is_debug_mode = false;
    String          session_id;

    virtual ~Core();

    // Lifecycle
    void InitHeadless(const String& url);
    void InitGui(const String& mlt_path, const String& url, const Vector<String>& clips_to_load = {});
    void PrepareShutdown();
    void FinishShutdown();

    // Accessors
    MainWindow*     GetWindow() { return window; }
    ProjectManager* GetProjectManager() { return project_manager; }
    CoolDoc*        GetCurrentDoc() { return current_doc; }
    Timecode        GetTimecode() const { return time_code; }
    MonitorManager* GetMonitorManager() { return monitor_manager; }
    MediaBrowser*   GetMediaBrowser() { return media_browser; }
    Bin*            GetBin() { return bin_view; }
    Bin*            GetActiveBin() { return active_bin_view; }
    
    std::shared_ptr<ProjectItemModel> GetProjectItemModel() { return project_item_model; }
    
    // UI Helpers
    void SelectBinClip(const String& id, bool activate_monitor = true, int frame = -1, Point zone = Point(-1, -1));
    void SelectTimelineItem(int id);
    void DisplaySelectionMessage(const String& message);
    void DisplayMessage(const String& message, int message_type, int timeout = -1);
    
    // Profile management
    bool   SetCurrentProfile(const String& profile_path);
    double GetCurrentSar() const;
    double GetCurrentDar() const;
    double GetCurrentFps() const;
    Size   GetCurrentFrameSize() const;
    
    // MLT Integration
    std::unique_ptr<Mlt::Repository>& GetMltRepository();
    ::Mlt::Profile& GetProjectProfile();
    
    // Logic
    void PushUndo(const std::function<bool()>& undo, const std::function<bool()>& redo, const String& text);
    void PushUndo(QUndoCommand* command);
    
    void UpdateItemKeyframes(ObjectId id);
    void InvalidateItem(ObjectId id);
    
    bool IsVertical() const;
    bool IsMediaCapturing() const;

private:
    Core(int package_type, bool debug_mode = false);
    static std::unique_ptr<Core> instance;

    // Component instances
    MainWindow*     window = nullptr;
    ProjectManager* project_manager = nullptr;
    MonitorManager* monitor_manager = nullptr;
    CoolDoc*        current_doc = nullptr;
    Bin*            bin_view = nullptr;
    Bin*            active_bin_view = nullptr;
    
    std::shared_ptr<ProjectItemModel> project_item_model;
    LibraryWidget*  library_view = nullptr;
    SubtitleEdit*   subtitle_widget = nullptr;
    TextBasedEdit*  text_edit_widget = nullptr;
    GuidesList*     guides_list = nullptr;
    TimeRemap*      time_remap_widget = nullptr;
    MixerManager*   mixer_widget = nullptr;
    MediaBrowser*   media_browser = nullptr;

    String          current_profile_path;
    int             package_type_id;
    Timecode        time_code;
    
    bool            is_gui_constructed = false;
    Splash*         splash_screen = nullptr;

    // Internal methods
    void InitLocale();
    void CheckProfileValidity();
    void BuildSplash(bool first_run, bool show_welcome, bool show_crash_recovery, bool was_upgraded);
};

END_UPP_NAMESPACE

#endif
