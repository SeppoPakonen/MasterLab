/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_assets_assetlist_view_AssetIconProvider_h_
#define _Cool_assets_assetlist_view_AssetIconProvider_h_

#include "../../../Cool.h"

NAMESPACE_UPP

/** @class AssetIconProvider
    @brief Helper for generating and caching icons for assets.
 */
class AssetIconProvider {
public:
    AssetIconProvider(bool is_effect);
    virtual ~AssetIconProvider();

    Image MakeIcon(const String& name);

private:
    bool is_effect;
    
    // U++ Image cache (placeholder for native Caching)
    static VectorMap<String, Image> icon_cache;
    
    Image CreateIcon(const String& name);
};

END_UPP_NAMESPACE

#endif
