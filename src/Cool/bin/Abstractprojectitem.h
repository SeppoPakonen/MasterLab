/*
    SPDX-FileCopyrightText: 2012 Till Theato <root@ttill.de>
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_AbstractProjectItem_h_
#define _Cool_AbstractProjectItem_h_

#include "../abstractmodel/Treeitem.hpp"

NAMESPACE_UPP

class ProjectClip;
class ProjectFolder;
class ProjectItemModel;

class AbstractProjectItem : public TreeItem {
public:
    enum ProjectItemType { FolderItem, ClipItem, SubClipItem, SubSequenceItem };

    AbstractProjectItem(ProjectItemType type, const String& id, 
                        const std::shared_ptr<ProjectItemModel>& model, bool is_root = false);
    virtual ~AbstractProjectItem();

    // Type access
    ProjectItemType GetItemType() const { return item_type; }
    virtual ClipType::ProducerType GetClipType() const = 0;

    // Hierarchy search
    virtual std::shared_ptr<ProjectClip>   GetClip(const String& id) = 0;
    virtual std::shared_ptr<ProjectFolder> GetFolder(const String& id) = 0;
    
    // Properties
    const String& GetBinId() const { return bin_id; }
    const String& GetName() const { return name; }
    virtual void  SetName(const String& n) { name = n; }
    virtual bool  HasAudioAndVideo() const = 0;
    
    // Data interface
    virtual QVariant GetData(int role) const;
    virtual bool     Rename(const String& name, int column) = 0;

protected:
    ProjectItemType item_type;
    String bin_id;
    String name;
    String description;
    Image  thumbnail;
    Time   date;
    
    uint total_usage = 0;
    FileStatus::ClipStatus clip_status;
};

END_UPP_NAMESPACE

#endif
