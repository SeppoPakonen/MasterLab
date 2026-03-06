/*
SPDX-FileCopyrightText: 2012 Till Theato <root@ttill.de>
SPDX-FileCopyrightText: 2014 Jean-Baptiste Mardelle <jb@kdenlive.org>
U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_ProjectItemModel_h_
#define _Cool_ProjectItemModel_h_

#include "../Definitions.h"
#include "../abstractmodel/Abstracttreemodel.hpp"

namespace Mlt {
    class Producer;
    class Properties;
    class Tractor;
    class Service;
}

NAMESPACE_UPP

class BinPlaylist;
class FileWatcher;
class ProjectClip;
class ProjectFolder;
class EffectStackModel;

class ProjectItemModel : public AbstractTreeModel {
public:
    friend class TreeItem;
    typedef ProjectItemModel CLASSNAME;

    static std::shared_ptr<ProjectItemModel> Construct();
    virtual ~ProjectItemModel();

    // Playlist management
    void BuildPlaylist(const String& uuid);
    
    // Item access
    std::shared_ptr<ProjectClip>   GetClipByBinID(const String& bin_id) const;
    std::shared_ptr<ProjectFolder> GetFolderByBinId(const String& bin_id);
    std::shared_ptr<ProjectFolder> GetRootFolder() const;
    
    // Stats and state
    int  ClipsCount() const;
    bool HasProxies() const;
    
    // MLT Integration
    std::shared_ptr<::Mlt::Tractor> GetProjectTractor();
    void StoreSequence(const String& uuid, std::shared_ptr<::Mlt::Tractor> tractor, bool internal_save = true);

protected:
    ProjectItemModel();

private:
    std::unique_ptr<BinPlaylist> bin_playlist;
    std::unique_ptr<FileWatcher> file_watcher;
    
    std::shared_ptr<::Mlt::Tractor> project_tractor;
    std::unordered_map<String, std::shared_ptr<::Mlt::Tractor>> extra_playlists;
    
    String model_uuid;
};

END_UPP_NAMESPACE

#endif
