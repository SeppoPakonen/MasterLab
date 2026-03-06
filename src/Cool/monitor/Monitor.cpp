/*
    SPDX-FileCopyrightText: 2007 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#include "Monitor.h"
#include "Monitormanager.h"
#include "Videowidget.h"
#include "../Core.h"
#include "../bin/Projectclip.h"
#include <mlt++/MltProducer.h>

NAMESPACE_UPP

Monitor::Monitor(Kdenlive::MonitorId id, MonitorManager* manager, MainWindow* parent)
    : AbstractMonitor(id, manager)
    , monitor_id(id)
    , manager(manager)
{
    video_widget = new VideoWidget();
    
    Add(video_widget->SizePos());
    
    AddFrame(tool_bar);
    tool_bar.Set(THISBACK(SetupToolbar));
    
    BuildUI();
}

Monitor::~Monitor() {
    if (video_widget) delete video_widget;
}

void Monitor::BuildUI() {
}

void Monitor::ResetProfile() {
}

void Monitor::ResetConsumer(bool full_reset) {
}

void Monitor::SetupMenu(Bar& bar) {
    bar.Add("Play", THISBACK(Play));
    bar.Add("Stop", THISBACK(Stop));
    bar.Separator();
    bar.Add("Mute", [=]{ Mute(true); });
}

void Monitor::SetupToolbar(Bar& bar) {
    bar.Add("Play", CtrlImg::plus(), THISBACK(Play)); 
    bar.Add("Stop", CtrlImg::minus(), THISBACK(Stop));
}

const String Monitor::GetActiveClipId(bool with_sequence) {
    // Resolve ambiguity by choosing one or casting if needed
    // return controller ? controller->AbstractProjectItem::GetBinId() : "";
    return controller ? controller->GetBinId() : "";
}

void Monitor::UpdateTimecodeFormat() {
}

void Monitor::ReloadProducer(const String& id) {
}

double Monitor::GetFps() const {
    return pCore.GetCurrentFps();
}

Size Monitor::GetProfileSize() const {
    return pCore.GetCurrentFrameSize();
}

void Monitor::Mute(bool m) {
}

void Monitor::Stop() {
    if (video_widget) {
        video_widget->Stop();
    }
}

void Monitor::Start() {
}

void Monitor::Play() {
}

void Monitor::Rewind(double speed) {
}

void Monitor::Forward(double speed, bool allow_normal_play) {
}

void Monitor::RefreshMonitorIfActive(bool direct_update) {
}

void Monitor::MouseSeek(int event_delta, int modifiers) {
}

void Monitor::SwitchFullScreen(bool minimize_only) {
}

void Monitor::Seek(int pos) {
    position = pos;
    if (WhenSeek) WhenSeek(pos);
}

void Monitor::RefreshMonitor(bool visible) {
    if (visible && video_widget) {
        video_widget->Refresh();
    }
}

void Monitor::Layout() {
}

void Monitor::Paint(Draw& draw) {
}

void Monitor::MouseMove(Point p, dword flags) {
}

void Monitor::LeftDown(Point p, dword flags) {
}

void Monitor::MouseWheel(Point p, int zdelta, dword flags) {
}

END_UPP_NAMESPACE
