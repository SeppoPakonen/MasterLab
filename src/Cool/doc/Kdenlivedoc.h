/*
    SPDX-FileCopyrightText: 2007 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_CoolDoc_h_
#define _Cool_CoolDoc_h_

#include <Core/Core.h>
#include "../Definitions.h"
#include "../utils/Gentime.h"
#include "../utils/Timecode.h"

NAMESPACE_UPP

// Forward declarations
class MainWindow;
class ProjectClip;
class MarkerListModel;
class DocUndoStack;
class TimelineItemModel;
class SubtitleModel;

namespace Mlt {
    class Profile;
}

class CoolDoc;

/** Result object for project opening */
class DocOpenResult {
public:
    bool IsSuccessful() const { return succeeded; }
    bool IsAborted() const { return aborted; }
    
    std::unique_ptr<CoolDoc> GetDocument() { return std::move(doc); }
    String GetError() const { return error_message; }
    
    bool WasUpgraded() const { return upgraded; }
    bool WasModified() const { return modified; }
    
    void SetDocument(std::unique_ptr<CoolDoc> d) { doc = std::move(d); succeeded = true; }
    void SetError(const String& e) { error_message = e; }
    void SetAborted() { aborted = true; }
    void SetUpgraded(bool u) { upgraded = u; }
    void SetModified(bool m) { modified = m; }

private:
    std::unique_ptr<CoolDoc> doc;
    String error_message;
    bool upgraded = false;
    bool modified = false;
    bool succeeded = false;
    bool aborted = false;
};

class CoolDoc {
public:
    CoolDoc(const String& project_folder, const String& profile_name, 
            const KdenliveStringMap& properties, const KdenliveStringMap& metadata, 
            const std::pair<int, int>& tracks, int audio_channels, MainWindow* parent = nullptr);
            
    static DocOpenResult Open(const String& url, const String& project_folder, bool recover_corruption, MainWindow* parent = nullptr);
    
    virtual ~CoolDoc();

    // State
    String active_uuid;
    bool   is_loading = true;
    bool   is_closing = false;
    bool   is_modified = false;

    // Accessors
    double GetFps() const;
    Size   GetFrameSize() const;
    String GetUrl() const { return url; }
    Timecode GetTimecode() const;
    std::shared_ptr<DocUndoStack> GetCommandStack() { return command_stack; }

    // Properties
    void   SetDocumentProperty(const String& name, const String& value);
    String GetDocumentProperty(const String& name, const String& default_value = "") const;
    bool   HasDocumentProperty(const String& name) const;

    // Layout/Timeline logic
    void   AddTimeline(const String& uuid, std::shared_ptr<TimelineItemModel> model);
    std::shared_ptr<TimelineItemModel> GetTimeline(const String& uuid);
    
    // Status
    bool IsModified() const { return is_modified; }
    void SetModified(bool mod = true) { is_modified = mod; }

private:
    String url;
    String project_folder;
    KdenliveStringMap document_properties;
    KdenliveStringMap document_metadata;
    
    std::shared_ptr<DocUndoStack> command_stack;
    VectorMap<String, std::shared_ptr<TimelineItemModel>> timelines;
    
    void InitializeProperties(bool new_doc = true);
};

END_UPP_NAMESPACE

#endif
