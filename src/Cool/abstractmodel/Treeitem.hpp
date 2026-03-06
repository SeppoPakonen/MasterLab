/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_abstractmodel_TreeItem_h_
#define _Cool_abstractmodel_TreeItem_h_

#include "../Definitions.h"

NAMESPACE_UPP

class AbstractTreeModel;

/** @class TreeItem
    @brief This class represents an item in a TreeModel
 */
class TreeItem : public std::enable_shared_from_this<TreeItem> {
public:
    TreeItem(const std::shared_ptr<AbstractTreeModel>& model, int id, bool is_root = false);
    virtual ~TreeItem();

    // Hierarchy
    std::shared_ptr<TreeItem> GetParent() const { return parent.lock(); }
    int  GetChildCount() const { return children.GetCount(); }
    std::shared_ptr<TreeItem> GetChild(int row) const;
    int  GetRow() const;
    
    // Model link
    std::shared_ptr<AbstractTreeModel> GetModel() const { return model.lock(); }
    int  GetId() const { return id; }

protected:
    std::weak_ptr<AbstractTreeModel> model;
    std::weak_ptr<TreeItem> parent;
    Vector<std::shared_ptr<TreeItem>> children;
    
    int id;
    bool is_root;

    virtual void UpdateParent(std::shared_ptr<TreeItem> new_parent);
};

END_UPP_NAMESPACE

#endif
