/*
    SPDX-FileCopyrightText: 2012 Till Theato <root@ttill.de>
    SPDX-FileCopyrightText: 2014 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_ProjectFolder_h_
#define _Cool_ProjectFolder_h_

#include "Abstractprojectitem.h"

NAMESPACE_UPP

class ProjectFolder : public AbstractProjectItem {
public:
    typedef ProjectFolder CLASSNAME;

    static std::shared_ptr<ProjectFolder> Construct(const String& id, const String& name, 
                                                    const std::shared_ptr<ProjectItemModel>& model);
    static std::shared_ptr<ProjectFolder> Construct(const std::shared_ptr<ProjectItemModel>& model);

    virtual ~ProjectFolder();

    // AbstractProjectItem implementation
    virtual std::shared_ptr<ProjectClip>   GetClip(const String& id) override;
    virtual std::shared_ptr<ProjectFolder> GetFolder(const String& id) override;
    virtual ClipType::ProducerType         GetClipType() const override { return ClipType::Unknown; }
    virtual bool Rename(const String& name, int column) override;

    // Logic
    Vector<std::shared_ptr<ProjectClip>> GetChildClips();
    bool HasChildClips() const;
    bool HasAudioAndVideo() const override { return false; }

protected:
    ProjectFolder(const String& id, const String& name, const std::shared_ptr<ProjectItemModel>& model);
    ProjectFolder(const std::shared_ptr<ProjectItemModel>& model);
};

END_UPP_NAMESPACE

#endif
