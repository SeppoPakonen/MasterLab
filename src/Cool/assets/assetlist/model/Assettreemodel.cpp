/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#include "Assettreemodel.hpp"
#include "../../../abstractmodel/Treeitem.hpp"

NAMESPACE_UPP

AssetTreeModel::AssetTreeModel()
    : AbstractTreeModel()
{
}

AssetTreeModel::~AssetTreeModel() {
}

String AssetTreeModel::GetName(int item_id) const {
    auto item = GetItemById(item_id);
    if (!item) return "";
    
    // In U++, we typically return data from the item's internal storage
    // return item->GetData(NameCol).ToString();
    return "";
}

bool AssetTreeModel::IsFavorite(int item_id, bool is_effect) const {
    auto item = GetItemById(item_id);
    if (!item) return false;
    
    // return item->GetData(FavCol).To<bool>();
    return false;
}

String AssetTreeModel::GetDescription(bool is_effect, int item_id) const {
    auto item = GetItemById(item_id);
    if (!item) return "";
    
    // TODO: Query from EffectsRepository or TransitionsRepository
    return "";
}

QVariant AssetTreeModel::GetData(const QModelIndex& index, int role) const {
    if (!index.isValid()) return QVariant();

    auto item = GetItemById(index.row());
    if (!item) return QVariant();

    switch (role) {
        case IdRole:
            // return item->GetData(IdCol);
            break;
        case FavoriteRole:
            // return item->GetData(FavCol);
            break;
        case NameRole:
        case Qt::DisplayRole:
            // return item->GetData(index.column());
            break;
    }
    
    return QVariant();
}

END_UPP_NAMESPACE
