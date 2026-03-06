/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#include "Treeitem.hpp"
#include "Abstracttreemodel.hpp"

NAMESPACE_UPP

TreeItem::TreeItem(const std::shared_ptr<AbstractTreeModel>& model, int id, bool is_root)
    : model(model)
    , id(id)
    , is_root(is_root)
{
}

TreeItem::~TreeItem() {
    if (auto ptr = model.lock()) {
        ptr->DeregisterItem(id, this);
    }
}

std::shared_ptr<TreeItem> TreeItem::GetChild(int row) const {
    if (row >= 0 && row < children.GetCount()) {
        return children[row];
    }
    return nullptr;
}

int TreeItem::GetRow() const {
    if (auto p = parent.lock()) {
        for (int i = 0; i < p->children.GetCount(); i++) {
            if (p->children[i].get() == this) {
                return i;
            }
        }
    }
    return 0;
}

void TreeItem::UpdateParent(std::shared_ptr<TreeItem> new_parent) {
    parent = new_parent;
}

END_UPP_NAMESPACE
