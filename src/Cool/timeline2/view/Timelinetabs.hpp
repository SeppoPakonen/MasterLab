/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_timeline2_view_TimelineTabs_h_
#define _Cool_timeline2_view_TimelineTabs_h_

#include <CtrlLib/CtrlLib.h>
#include "../../Definitions.h"

NAMESPACE_UPP

class TimelineWidget;
class TimelineItemModel;
class MainWindow;

/** @class TimelineTabs
    @brief Container for multiple timeline sequence tabs.
 */
class TimelineTabs : public TabCtrl {
public:
    typedef TimelineTabs CLASSNAME;

    TimelineTabs(MainWindow* parent = nullptr);
    virtual ~TimelineTabs();

    TimelineWidget* GetCurrentTimeline() const;
    bool RaiseTimeline(const String& uuid);
    
    TimelineWidget* AddTimeline(const String& uuid, const String& name, std::shared_ptr<TimelineItemModel> model);
    void CloseTimelineTab(const String& uuid);

    // Callbacks replacing Qt Signals
    Callback1<int> WhenZoomChanged;
    Callback       WhenFitZoom;

private:
    MainWindow* main_window;
    TimelineWidget* active_timeline = nullptr;
    
    VectorMap<String, TimelineWidget*> timeline_widgets;
    mutable Mutex lock;
    
    void OnTabChanged();
};

END_UPP_NAMESPACE

#endif
