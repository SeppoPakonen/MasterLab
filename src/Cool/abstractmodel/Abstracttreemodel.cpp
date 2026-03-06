/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#include "Abstracttreemodel.hpp"
#include "Treeitem.hpp"

NAMESPACE_UPP

int AbstractTreeModel::current_tree_id = 0;

AbstractTreeModel::AbstractTreeModel() {
}

AbstractTreeModel::~AbstractTreeModel() {
    all_items.clear();
    root_item.reset();
}

std::shared_ptr<AbstractTreeModel> AbstractTreeModel::Construct() {
    std::shared_ptr<AbstractTreeModel> self(new AbstractTreeModel());
    // self->root_item = TreeItem::Construct(self, GetNextId(), true);
    return self;
}

int AbstractTreeModel::GetRowCount(const QModelIndex& parent) const {
    if (parent.column() > 0) return 0;
    
    std::shared_ptr<TreeItem> parent_item;
    if (!parent.isValid()) {
        parent_item = root_item;
    } else {
        parent_item = GetItemById(parent.row());
    }
    
    return parent_item ? parent_item->GetChildCount() : 0;
}

int AbstractTreeModel::GetColumnCount(const QModelIndex& parent) const {
    return 1;
}

QVariant AbstractTreeModel::GetData(const QModelIndex& index, int role) const {
    return QVariant();
}

std::shared_ptr<TreeItem> AbstractTreeModel::GetItemById(int id) const {
    if (root_item && id == root_item->GetId()) {
        return root_item;
    }
    auto it = all_items.find(id);
    if (it != all_items.end()) {
        return it->second.lock();
    }
    return nullptr;
}

void AbstractTreeModel::RegisterItem(const std::shared_ptr<TreeItem>& item) {
    if (item) {
        all_items[item->GetId()] = item;
    }
}

void AbstractTreeModel::DeregisterItem(int id, TreeItem* item) {
    all_items.erase(id);
}

int AbstractTreeModel::GetNextId() {
    return current_tree_id++;
}

END_UPP_NAMESPACE
