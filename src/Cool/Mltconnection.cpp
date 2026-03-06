/*
SPDX-FileCopyrightText: 2007 Jean-Baptiste Mardelle <jb@kdenlive.org>
SPDX-FileCopyrightText: 2014 Till Theato <root@ttill.de>
SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
U++ Conversion: 2026 MasterLab Team
*/

#include "Mltconnection.h"
#include "Core.h"
#include "Mainwindow.h"

NAMESPACE_UPP

std::unique_ptr<MltConnection> MltConnection::instance;

MltConnection::MltConnection(const String& mlt_path) {
    // Disable VDPAU that crashes in multithread environment
    SetEnv("MLT_NO_VDPAU", "1");
    
    // After initializing the MLT factory, set the locale to C
    // to ensure numbers are always serialized with . as decimal point.
    // TODO: repository = std::unique_ptr<Mlt::Repository>(Mlt::Factory::init());
    
    // setlocale(MLT_LC_CATEGORY, nullptr);
    
    LocateMeltAndProfilesPath(mlt_path);
    
    // TODO: Retrieve producers list and set in Settings
    // mlt_log_set_level(MLT_LOG_ERROR);
    // mlt_log_set_callback(mlt_log_handler);
    
    RefreshLumas();
}

void MltConnection::Construct(const String& mlt_path) {
    if (instance) return;
    instance.reset(new MltConnection(mlt_path));
}

MltConnection& MltConnection::Self() {
    return *instance;
}

void MltConnection::LocateMeltAndProfilesPath(const String& mlt_path) {
    String profile_path = mlt_path;
    String lib_name = "mlt-7";
    
    // Environment variables override settings
    String env_path = GetEnv("MLT_PROFILES_PATH");
    if (profile_path.IsEmpty() && !env_path.IsEmpty()) {
        profile_path = env_path;
    }
    
    // Try to guess MLT path relative to executable
    if (profile_path.IsEmpty() || !DirectoryExists(profile_path)) {
        String app_path = GetFileDirectory(GetExeFilePath());
        profile_path = NormalizePath(app_path + "/../share/" + lib_name + "/profiles");
    }
    
    // TODO: Set profile path in Settings
    
    String melt_path;
    // TODO: Search for melt-7 executable using standard U++ FindFile or system paths
}

void MltConnection::RefreshLumas() {
    // TODO: Scan directories for luma files and update MainWindow caches
    Cout() << "Refreshing MLT Lumas..." << EOL;
}

END_UPP_NAMESPACE
