/*
    SPDX-FileCopyrightText: 2020 Jean-Baptiste Mardelle
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_dialogs_SubtitleEdit_h_
#define _Cool_dialogs_SubtitleEdit_h_

#include <CtrlLib/CtrlLib.h>
#include "../Definitions.h"
#include "../utils/Gentime.h"

NAMESPACE_UPP

class SubtitleModel;
class TimecodeDisplay;

class SubtitleEdit : public ParentCtrl {
public:
    typedef SubtitleEdit CLASSNAME;

    SubtitleEdit(MainWindow* parent = nullptr);
    virtual ~SubtitleEdit();

    void SetModel(std::shared_ptr<SubtitleModel> model);
    void SetActiveSubtitle(int id);

    // Callbacks for owner
    std::function<void(const String&)> WhenAddSubtitle;
    std::function<void(int, int)>      WhenCutSubtitle;

private:
    std::shared_ptr<SubtitleModel> model;
    int active_sub = -1;
    int layer;
    bool is_simple_edit = false;
    
    GenTime start_pos;
    GenTime end_pos;

    // UI Components
    DocEdit  sub_text;
    ToolBar  tool_bar;
    
    // Logic
    void UpdateSubtitle();
    void GoToPrevious();
    void GoToNext();
    void SyncSimpleText();
    
    void BuildUI();
};

END_UPP_NAMESPACE

#endif
