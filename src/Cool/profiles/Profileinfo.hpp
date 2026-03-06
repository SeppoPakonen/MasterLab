/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_profiles_ProfileInfo_h_
#define _Cool_profiles_ProfileInfo_h_

#include "../Cool.h"

namespace Mlt {
    class Profile;
}

NAMESPACE_UPP

/** @brief This is a virtual class that represents any profile that we can get info from
 */
class ProfileInfo {
public:
    ProfileInfo() = default;
    virtual ~ProfileInfo() = default;

    virtual bool   IsValid() const = 0;
    virtual String GetDescription() const = 0;
    virtual int    GetFrameRateNum() const = 0;
    virtual int    GetFrameRateDen() const = 0;
    virtual double GetFps() const = 0;
    virtual int    GetWidth() const = 0;
    virtual int    GetHeight() const = 0;
    virtual bool   IsProgressive() const = 0;
    virtual bool   IsBottomFieldFirst() const = 0;
    virtual int    GetSampleAspectNum() const = 0;
    virtual int    GetSampleAspectDen() const = 0;
    virtual double GetSar() const = 0;
    virtual int    GetDisplayAspectNum() const = 0;
    virtual int    GetDisplayAspectDen() const = 0;
    virtual double GetDar() const = 0;
    virtual int    GetColorspace() const = 0;
    String GetColorspaceDescription() const;
    virtual String GetPath() const = 0;

    bool operator==(const ProfileInfo& other) const;
    bool operator!=(const ProfileInfo& other) const { return !(*this == other); }

    bool IsCompatible(const std::unique_ptr<ProfileInfo>& other) const;
    bool IsCompatible(::Mlt::Profile* other) const;
    bool HasValidFps() const;

    virtual void AdjustDimensions() = 0;

    const String GetDescriptiveString() const;
    const String GetDialogDescriptiveString() const;
};

END_UPP_NAMESPACE

#endif
