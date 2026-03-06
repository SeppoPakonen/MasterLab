/*
    SPDX-FileCopyrightText: 2012 Till Theato <root@ttill.de>
    SPDX-FileCopyrightText: 2014 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_ProjectClip_h_
#define _Cool_ProjectClip_h_

#include "Abstractprojectitem.h"
#include "../mltcontroller/Clipcontroller.h"

NAMESPACE_UPP

class ProjectSubClip;

class ProjectClip : public AbstractProjectItem, public ClipController {
public:
    typedef ProjectClip CLASSNAME;

    static std::shared_ptr<ProjectClip> Construct(const String& id, const Image& thumb, 
                                                  const std::shared_ptr<ProjectItemModel>& model,
                                                  std::shared_ptr<::Mlt::Producer>& producer);
    
    virtual ~ProjectClip();

    // AbstractProjectItem implementation
    virtual std::shared_ptr<ProjectClip>   GetClip(const String& id) override { return (id == bin_id) ? std::static_pointer_cast<ProjectClip>(shared_from_this()) : nullptr; }
    virtual std::shared_ptr<ProjectFolder> GetFolder(const String& id) override { return nullptr; }
    virtual ClipType::ProducerType         GetClipType() const override { return ClipController::GetClipType(); }
    virtual bool Rename(const String& name, int column) override;

    // ClipController implementation
    virtual std::unique_ptr<::Mlt::Producer> GetThumbProducer(const String& uuid = "") override;
    virtual void SetThumbFrame(int frame) override;
    virtual void ReloadProducer(bool refresh_only = false, bool is_proxy = false, bool force_audio_reload = false) override;

    // Logic
    virtual bool HasAudioAndVideo() const override;
    const String GetHash();

protected:
    ProjectClip(const String& id, const Image& thumb, const std::shared_ptr<ProjectItemModel>& model, std::shared_ptr<::Mlt::Producer>& producer);

private:
    Mutex thumb_mutex;
    bool  is_reloading = false;
};

END_UPP_NAMESPACE

#endif
