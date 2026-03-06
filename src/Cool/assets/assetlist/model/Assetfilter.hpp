/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_assets_assetlist_model_AssetFilter_h_
#define _Cool_assets_assetlist_model_AssetFilter_h_

#include "../../../Definitions.h"

NAMESPACE_UPP

class TreeItem;

/** @class AssetFilter
    @brief Helper for filtering and sorting asset lists in UI components.
 */
class AssetFilter {
public:
    AssetFilter();
    virtual ~AssetFilter();

    void SetFilterName(bool enabled, const String& pattern);
    void SetIncludeList(bool enabled);
    
    bool IsVisible(const std::shared_ptr<TreeItem>& item) const;
    virtual void ReloadFilterOnFavorite() {} // Default implementation

protected:
    bool FilterName(const std::shared_ptr<TreeItem>& item) const;
    static String NormalizeText(const String& text);
    virtual bool ApplyAll(std::shared_ptr<TreeItem> item) const;

    bool   name_enabled = false;
    bool   include_list_enabled = false;
    String name_value;
};

END_UPP_NAMESPACE

#endif
