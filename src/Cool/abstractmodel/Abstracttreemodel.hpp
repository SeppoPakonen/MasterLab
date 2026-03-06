/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_abstractmodel_AbstractTreeModel_h_
#define _Cool_abstractmodel_AbstractTreeModel_h_

#include "../Definitions.h"

NAMESPACE_UPP

class TreeItem;

/** @class AbstractTreeModel
    @brief This class represents a generic tree hierarchy
 */
class AbstractTreeModel : public std::enable_shared_from_this<AbstractTreeModel> {
public:
    AbstractTreeModel();
    virtual ~AbstractTreeModel();

    static std::shared_ptr<AbstractTreeModel> Construct();

    // Model interface
    virtual int GetRowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual int GetColumnCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QVariant GetData(const QModelIndex& index, int role) const;

    // Item management
    std::shared_ptr<TreeItem> GetItemById(int id) const;
    std::shared_ptr<TreeItem> GetRoot() const { return root_item; }

protected:
    std::shared_ptr<TreeItem> root_item;
    std::unordered_map<int, std::weak_ptr<TreeItem>> all_items;

    virtual void RegisterItem(const std::shared_ptr<TreeItem>& item);
    virtual void DeregisterItem(int id, TreeItem* item);

    static int GetNextId();
    static int current_tree_id;
};

END_UPP_NAMESPACE

#endif
