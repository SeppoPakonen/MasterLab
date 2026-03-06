/*
    SPDX-FileCopyrightText: 2021 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_dialogs_TimeRemap_h_
#define _Cool_dialogs_TimeRemap_h_

#include <CtrlLib/CtrlLib.h>
#include "../Definitions.h"

namespace Mlt {
    class Producer;
    class Properties;
}

NAMESPACE_UPP

class ProjectClip;

class RemapView : public ParentCtrl {
public:
    typedef RemapView CLASSNAME;
    RemapView();
    virtual ~RemapView();

    void SetBinClipDuration(std::shared_ptr<ProjectClip> clip, int duration);
    void SetDuration(std::shared_ptr<::Mlt::Producer> service, int duration, int source_duration = 0);
    
    virtual void Paint(Draw& draw) override;
    virtual void Layout() override;

private:
    int duration;
    int source_duration;
    int max_length;
    int position;
    
    Pointf zoom_handle;
    VectorMap<int, int> keyframes;
    
    std::shared_ptr<ProjectClip> clip;
    std::shared_ptr<::Mlt::Producer> service;
    
    void BuildUI();
};

class TimeRemap : public ParentCtrl {
public:
    typedef TimeRemap CLASSNAME;

    TimeRemap(MainWindow* parent = nullptr);
    virtual ~TimeRemap();

    void SelectedClip(int cid, const String& uuid);
    void SetClip(std::shared_ptr<ProjectClip> clip, int in = -1, int out = -1);
    
    const String& GetCurrentClip() const { return bin_id; }

private:
    RemapView* view;
    int cid;
    String uuid;
    String bin_id;
    
    ToolBar tool_bar;
    
    void UpdateKeyframes();
    void BuildUI();
};

END_UPP_NAMESPACE

#endif
