/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_project_dialogs_GuidesList_h_
#define _Cool_project_dialogs_GuidesList_h_

#include <CtrlLib/CtrlLib.h>
#include "../../Definitions.h"

NAMESPACE_UPP

class MarkerListModel;
class MarkerSortModel;

class GuidesList : public ParentCtrl {
public:
    typedef GuidesList CLASSNAME;

    GuidesList(MainWindow* parent = nullptr);
    virtual ~GuidesList();

    void SetModel(std::weak_ptr<MarkerListModel> model, std::shared_ptr<MarkerSortModel> view_model);

private:
    std::weak_ptr<MarkerListModel> marker_model;
    std::shared_ptr<MarkerSortModel> sort_model;
    
    // U++ UI Components
    ArrayCtrl  guides_table;
    ToolBar    tool_bar;
    
    void BuildUI();
    void OnSelectionChanged();
    void OnAddGuide();
};

END_UPP_NAMESPACE

#endif
