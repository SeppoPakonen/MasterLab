/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_assets_assetlist_model_AssetTreeModel_h_
#define _Cool_assets_assetlist_model_AssetTreeModel_h_

#include "../../../abstractmodel/Abstracttreemodel.hpp"

NAMESPACE_UPP

class AssetIconProvider;

/** @class AssetTreeModel
    @brief This class represents an effect/transition hierarchy to be displayed as a tree
 */
class AssetTreeModel : public AbstractTreeModel {
public:
    typedef AssetTreeModel CLASSNAME;

    enum { IdRole = 100, NameRole, FavoriteRole, TypeRole, IncludeListRole, TenBitRole };
    enum { NameCol = 0, IdCol = 1, TypeCol = 2, FavCol = 3, PreferredCol = 5, IncludeListCol = 6, TenBitCol = 7 };

    AssetTreeModel();
    virtual ~AssetTreeModel();

    // Accessors
    String GetName(int item_id) const;
    String GetDescription(bool is_effect, int item_id) const;
    bool   IsFavorite(int item_id, bool is_effect) const;

    // Model interface implementation
    virtual QVariant GetData(const QModelIndex& index, int role) const override;

    // Actions
    virtual void SetFavorite(int item_id, bool favorite, bool is_effect) = 0;
    virtual void DeleteEffect(int item_id) = 0;

protected:
    AssetIconProvider* asset_icon_provider = nullptr;
};

END_UPP_NAMESPACE

#endif
