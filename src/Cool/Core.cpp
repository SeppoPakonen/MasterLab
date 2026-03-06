/*
SPDX-FileCopyrightText: 2014 Till Theato <root@ttill.de>
SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
U++ Conversion: 2026 MasterLab Team
*/

#include "Core.h"
#include "Mainwindow.h"
#include "monitor/Monitormanager.h"
#include "project/Projectmanager.h"
#include "bin/Projectitemmodel.h"
#include "capture/Mediacapture.h"
#include "dialogs/Splash.hpp"
#include "Mltconnection.h"
#include "profiles/Profilerepository.hpp"
#include "audiomixer/Mixermanager.hpp"
#include "bin/Mediabrowser.h"
#include "library/Librarywidget.h"
#include "dialogs/Subtitleedit.h"
#include "dialogs/Textbasededit.h"
#include "dialogs/Timeremap.h"
#include "project/dialogs/Guideslist.h"

NAMESPACE_UPP

static bool inhibit_hide_bar_timer = false;

std::unique_ptr<Core> Core::instance;

Core& Core::Self() {
    if (!instance) {
        instance.reset(new Core(0));
    }
    return *instance;
}

Core::Core(int package_type, bool debug_mode)
    : is_debug_mode(debug_mode)
    , package_type_id(package_type)
{
    session_id = "placeholder-session-uuid"; 
}

Core::~Core() {
    FinishShutdown();
}

bool Core::Build(int package_type, bool test_mode, bool debug_mode, bool show_welcome) {
    if (instance) return true;
    
    instance.reset(new Core(package_type, debug_mode));
    instance->InitLocale();
    
    bool show_recovery = false;
    bool first_run = false;
    bool was_upgraded = false;
    
    if (!test_mode) {
        String lock_path = AppendFileName(GetTempDirectory(), "cool_lock");
        if (FileExists(lock_path)) {
            show_recovery = true;
        } else {
            SaveFile(lock_path, "");
        }
        
        instance->BuildSplash(first_run, show_welcome, show_recovery, was_upgraded);
    }
    
    instance->project_item_model = ProjectItemModel::Construct();
    instance->project_manager = new ProjectManager(instance.get());
    
    return true;
}

void Core::BuildDocks() {
    if (!window) return;
    
    mixer_widget = new MixerManager(window);
    media_browser = new MediaBrowser(window);
    library_view = new LibraryWidget(project_manager, window);
    subtitle_widget = new SubtitleEdit(window);
    text_edit_widget = new TextBasedEdit(window);
    time_remap_widget = new TimeRemap(window);
    guides_list = new GuidesList(window);
}

void Core::InitHeadless(const String& url) {
    MltConnection::Construct("");
    project_manager = new ProjectManager(this);
}

void Core::InitGui(const String& mlt_path, const String& url, const Vector<String>& clips_to_load) {
    window = new MainWindow();
    
    bool in_sandbox = (package_type_id == 1 || package_type_id == 2 || package_type_id == 3);
    if (in_sandbox) {
        String app_path = GetFileDirectory(GetExeFilePath());
        MltConnection::Construct(NormalizePath(app_path + "/../share/mlt/profiles"));
    } else {
        MltConnection::Construct(mlt_path);
    }
    
    monitor_manager = new MonitorManager(this);
    project_manager->Init(url, clips_to_load);
    window->Init();
    
    is_gui_constructed = true;
    
    ProfileRepository::Get()->Refresh();
    SetCurrentProfile(current_profile_path);
}

void Core::BuildSplash(bool first_run, bool show_welcome, bool show_crash_recovery, bool was_upgraded) {
    Cout() << "Building splash screen (Welcome: " << show_welcome << ")" << EOL;
}

void Core::InitLocale() {
}

void Core::PrepareShutdown() {
    is_gui_constructed = false;
}

void Core::FinishShutdown() {
    if (monitor_manager) { delete monitor_manager; monitor_manager = nullptr; }
    if (project_manager) { delete project_manager; project_manager = nullptr; }
    if (mixer_widget) { delete mixer_widget; mixer_widget = nullptr; }
    if (media_browser) { delete media_browser; media_browser = nullptr; }
    if (library_view) { delete library_view; library_view = nullptr; }
    if (subtitle_widget) { delete subtitle_widget; subtitle_widget = nullptr; }
    if (text_edit_widget) { delete text_edit_widget; text_edit_widget = nullptr; }
    if (time_remap_widget) { delete time_remap_widget; time_remap_widget = nullptr; }
    if (guides_list) { delete guides_list; guides_list = nullptr; }
}

bool Core::SetCurrentProfile(const String& profile_path) {
    if (current_profile_path == profile_path) return true;
    
    if (ProfileRepository::Get()->ProfileExists(profile_path)) {
        current_profile_path = profile_path;
        return true;
    }
    return false;
}

void Core::SelectBinClip(const String& id, bool activate_monitor, int frame, Point zone) {
    if (window && window->ActiveBin()) {
        window->ActiveBin()->SelectClipById(id, frame, zone, activate_monitor);
    }
}

void Core::SelectTimelineItem(int id) {
}

void Core::DisplayMessage(const String& message, int message_type, int timeout) {
    if (window) {
        window->DisplayMessage(message, message_type, timeout);
    } else {
        Cout() << "Core Message: " << message << EOL;
    }
}

void Core::DisplaySelectionMessage(const String& message) {
    if (window) {
        window->DisplaySelectionMessage(message);
    }
}

double Core::GetCurrentFps() const {
    return 25.0;
}

Size Core::GetCurrentFrameSize() const {
    return Size(1920, 1080);
}

bool Core::IsVertical() const {
    Size sz = GetCurrentFrameSize();
    return sz.cy > sz.cx;
}

void Core::PushUndo(const std::function<bool()>& undo, const std::function<bool()>& redo, const String& text) {
}

void Core::PushUndo(QUndoCommand* command) {
}

void Core::UpdateItemKeyframes(ObjectId id) {
}

void Core::InvalidateItem(ObjectId id) {
}

bool Core::IsMediaCapturing() const {
    return false;
}

void Core::Clean() {
    instance.reset();
}

END_UPP_NAMESPACE
