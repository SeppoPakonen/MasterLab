/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_bin_BinPlaylist_h_
#define _Cool_bin_BinPlaylist_h_

#include "../Definitions.h"

namespace Mlt {
    class Playlist;
    class Producer;
    class Tractor;
}

NAMESPACE_UPP

class AbstractProjectItem;

/** @class BinPlaylist
    @brief This class is a wrapper around a melt playlist that allows one to store the Bin.
 */
class BinPlaylist {
public:
    BinPlaylist(const String& uuid);
    virtual ~BinPlaylist();

    void ManageBinItemDeletion(AbstractProjectItem* bin_elem);
    void ManageBinItemInsertion(const std::shared_ptr<AbstractProjectItem>& bin_elem);
    void ManageBinFolderRename(const std::shared_ptr<AbstractProjectItem>& bin_elem);

    void SetRetainIn(::Mlt::Tractor* model_tractor);
    void SaveDocumentProperties(const KdenliveStringMap& props, const KdenliveStringMap& metadata);
    void SaveProperty(const String& name, const String& value);

    KdenliveStringMap GetProxies(const String& root);
    const String GetSequenceId(const String& uuid);
    bool HasSequenceId(const String& uuid) const;

    int GetCount() const;

private:
    std::unique_ptr<::Mlt::Playlist> bin_playlist;
    String uuid;
    std::unordered_set<String> all_clips;
    VectorMap<String, String> sequence_clips;
};

END_UPP_NAMESPACE

#endif
