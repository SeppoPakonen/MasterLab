/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_assets_AssetPanel_h_
#define _Cool_assets_AssetPanel_h_

#include <CtrlLib/CtrlLib.h>
#include "../Definitions.h"

NAMESPACE_UPP

class AssetParameterModel;
class EffectStackModel;
class MainWindow;

/** @class AssetPanel
    @brief Widget for interacting with the currently selected asset (effects/transitions).
 */
class AssetPanel : public ParentCtrl {
public:
    typedef AssetPanel CLASSNAME;

    AssetPanel(MainWindow* parent = nullptr);
    virtual ~AssetPanel();

    // Model display
    void ShowTransition(int tid, const std::shared_ptr<AssetParameterModel>& transition_model);
    void ShowMix(int cid, const std::shared_ptr<AssetParameterModel>& transition_model, bool refresh_only);
    void ShowEffectStack(const String& item_name, const std::shared_ptr<EffectStackModel>& effects_model, Size frame_size, bool show_keyframes);

    void Clear();

    // State access
    ObjectId GetEffectStackOwner();
    bool     AddEffect(const String& effect_id);
    
    bool HasRunningTask() const { return false; }

    // Event Handlers
    void ClearAssetPanel(int item_id);
    void DeleteCurrentEffect();
    void CollapseCurrentEffect();

protected:
    virtual void Layout() override;

private:
    MainWindow* main_window;
    
    // UI Components
    Label      asset_title;
    ParentCtrl container;
    ScrollArea scroll_view;
    
    // Sub-views (Forward declared or placeholders)
    Ptr<Ctrl>  active_widget;
    
    void BuildUI();
};

END_UPP_NAMESPACE

#endif
