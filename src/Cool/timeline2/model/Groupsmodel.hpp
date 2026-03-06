/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_GroupsModel_h_
#define _Cool_GroupsModel_h_

#include "../../Definitions.h"
#include "../../Undohelper.hpp"

NAMESPACE_UPP

class TimelineItemModel;

/** @class GroupsModel
    @brief This class represents the group hierarchy for timeline items.
 */
class GroupsModel {
public:
    GroupsModel(std::weak_ptr<TimelineItemModel> parent);
    virtual ~GroupsModel();

    // Grouping operations
    int  GroupItems(const std::unordered_set<int>& ids, Fun& undo, Fun& redo, GroupType type = GroupType::Normal, bool force = false);
    bool UngroupItem(int id, Fun& undo, Fun& redo, bool delete_orphan = true);

    void CreateGroupItem(int id);
    bool DestructGroupItem(int id);

    // Hierarchy access
    int  GetRootId(int id) const;
    bool IsLeaf(int id) const;
    bool IsInGroup(int id) const;
    
    std::unordered_set<int> GetSubtree(int id) const;
    std::unordered_set<int> GetLeaves(int id) const;
    std::unordered_set<int> GetDirectChildren(int id) const;
    int GetDirectAncestor(int id) const;
    
    GroupType GetType(int id) const;

    // Persistence
    String ToJson() const;
    bool FromJson(const String& data);

private:
    std::weak_ptr<TimelineItemModel> parent;

    std::unordered_map<int, int> up_link; // item -> parent_group
    std::unordered_map<int, std::unordered_set<int>> down_link; // group -> children
    std::unordered_map<int, GroupType> group_ids; // group -> type
    
    mutable Mutex lock;
    
    void PromoteToGroup(int gid, GroupType type);
    void DowngradeToLeaf(int gid);
};

END_UPP_NAMESPACE

#endif
