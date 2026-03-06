/*
    SPDX-FileCopyrightText: 2007 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#include "Kdenlivedoc.h"
#include "../Core.h"
#include "../Mainwindow.h"
#include "../project/Projectmanager.h"
#include "../bin/Projectitemmodel.h"
#include "../doc/Docundostack.hpp"

NAMESPACE_UPP

CoolDoc::CoolDoc(const String& project_folder, const String& profile_name, 
                 const KdenliveStringMap& properties, const KdenliveStringMap& metadata, 
                 const std::pair<int, int>& tracks, int audio_channels, MainWindow* parent)
    : project_folder(project_folder)
    , document_properties(properties)
    , document_metadata(metadata)
{
    active_uuid = "placeholder-active-uuid";
    command_stack = std::make_shared<DocUndoStack>();
    
    pCore.SetCurrentProfile(profile_name);
    InitializeProperties(true);
}

CoolDoc::~CoolDoc() {
}

DocOpenResult CoolDoc::Open(const String& url, const String& project_folder, bool recover_corruption, MainWindow* parent) {
    DocOpenResult result;
    
    if (url.IsEmpty()) {
        result.SetError("Invalid file path");
        return result;
    }

    if (!FileExists(url)) {
        result.SetError("File does not exist: " + url);
        return result;
    }

    // TODO: U++ Migration - Implement real XML parsing and validation
    // For now, create a dummy document to satisfy the architecture
    KdenliveStringMap props, meta;
    auto doc = std::unique_ptr<CoolDoc>(new CoolDoc(project_folder, "atsc_1080p_25", props, meta, {2, 2}, 2, parent));
    doc->url = url;
    
    result.SetDocument(std::move(doc));
    return result;
}

void CoolDoc::InitializeProperties(bool new_doc) {
    // Set default properties
    if (new_doc) {
        document_properties.GetAdd("documentid") = Format("%lld", GetSysTime().Get());
    }
}

double CoolDoc::GetFps() const {
    return pCore.GetCurrentFps();
}

Size CoolDoc::GetFrameSize() const {
    return pCore.GetCurrentFrameSize();
}

Timecode CoolDoc::GetTimecode() const {
    return pCore.GetTimecode();
}

void CoolDoc::SetDocumentProperty(const String& name, const String& value) {
    document_properties.GetAdd(name) = value;
    SetModified(true);
}

String CoolDoc::GetDocumentProperty(const String& name, const String& default_value) const {
    int idx = document_properties.Find(name);
    return (idx >= 0) ? document_properties[idx] : default_value;
}

bool CoolDoc::HasDocumentProperty(const String& name) const {
    return document_properties.Find(name) >= 0;
}

void CoolDoc::AddTimeline(const String& uuid, std::shared_ptr<TimelineItemModel> model) {
    timelines.Add(uuid, model);
}

std::shared_ptr<TimelineItemModel> CoolDoc::GetTimeline(const String& uuid) {
    int idx = timelines.Find(uuid);
    return (idx >= 0) ? timelines[idx] : nullptr;
}

END_UPP_NAMESPACE
