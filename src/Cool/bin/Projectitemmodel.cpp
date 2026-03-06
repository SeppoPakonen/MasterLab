/*
SPDX-FileCopyrightText: 2012 Till Theato <root@ttill.de>
SPDX-FileCopyrightText: 2014 Jean-Baptiste Mardelle <jb@kdenlive.org>
U++ Conversion: 2026 MasterLab Team
*/

#include "Projectitemmodel.h"
#include "Bin.h"
#include "../Core.h"
#include "Projectclip.h"
#include "Projectfolder.h"
#include "Binplaylist.hpp"
#include "Filewatcher.hpp"
#include <mlt++/Mlt.h>

NAMESPACE_UPP

ProjectItemModel::ProjectItemModel()
    : AbstractTreeModel()
{
    model_uuid = "placeholder-uuid";
    file_watcher.reset(new FileWatcher());
}

std::shared_ptr<ProjectItemModel> ProjectItemModel::Construct() {
    std::shared_ptr<ProjectItemModel> self(new ProjectItemModel());
    // self->root_item = ProjectFolder::Construct(self);
    return self;
}

ProjectItemModel::~ProjectItemModel() {
}

void ProjectItemModel::BuildPlaylist(const String& uuid) {
    model_uuid = uuid;
    file_watcher->Clear();
    extra_playlists.clear();
    
    // TODO: U++ Migration - Initialize MLT Tractor and BinPlaylist
    // project_tractor = std::make_shared<::Mlt::Tractor>(pCore.GetProjectProfile());
    // bin_playlist.reset(new BinPlaylist(uuid));
}

std::shared_ptr<ProjectClip> ProjectItemModel::GetClipByBinID(const String& bin_id) const {
    // TODO: Search in item tree
    return nullptr;
}

std::shared_ptr<ProjectFolder> ProjectItemModel::GetFolderByBinId(const String& bin_id) {
    // TODO: Search in item tree
    return nullptr;
}

std::shared_ptr<ProjectFolder> ProjectItemModel::GetRootFolder() const {
    // return std::static_pointer_cast<ProjectFolder>(root_item);
    return nullptr;
}

int ProjectItemModel::ClipsCount() const {
    return 0; // TODO: Implement count
}

bool ProjectItemModel::HasProxies() const {
    return false; // TODO: Check all clips
}

std::shared_ptr<::Mlt::Tractor> ProjectItemModel::GetProjectTractor() {
    return project_tractor;
}

void ProjectItemModel::StoreSequence(const String& uuid, std::shared_ptr<::Mlt::Tractor> tractor, bool internal_save) {
    extra_playlists[uuid] = tractor;
}

END_UPP_NAMESPACE
