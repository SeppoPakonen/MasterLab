/*
    SPDX-FileCopyrightText: 2021 Jean-Baptiste Mardelle
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_dialogs_TextBasedEdit_h_
#define _Cool_dialogs_TextBasedEdit_h_

#include <CtrlLib/CtrlLib.h>
#include "../Definitions.h"

NAMESPACE_UPP

class ProjectClip;

class VideoTextEdit : public DocEdit {
public:
    typedef VideoTextEdit CLASSNAME;
    VideoTextEdit();
    
    virtual void Paint(Draw& draw) override;
    virtual void Layout() override;
    
    int GetLineNumberAreaWidth();
    void RebuildZones();

private:
    Vector<Point> speech_zones;
    Vector<Point> cut_zones;
    
    int hovered_block = -1;
    int last_clicked_block = -1;
    Vector<int> selected_blocks;
};

class TextBasedEdit : public ParentCtrl {
public:
    typedef TextBasedEdit CLASSNAME;

    TextBasedEdit();
    virtual ~TextBasedEdit();

    void OpenClip(std::shared_ptr<ProjectClip> clip);
    void DeleteItem();

private:
    String bin_id;
    String ref_id;
    String source_url;
    double clip_duration = 0.0;
    
    VideoTextEdit* visual_editor;
    ToolBar        tool_bar;
    
    void StartRecognition();
    void InsertToTimeline();
    void CreateSequence();
    
    void BuildUI();
};

END_UPP_NAMESPACE

#endif
