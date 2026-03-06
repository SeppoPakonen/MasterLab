/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_profiles_ProfileRepository_h_
#define _Cool_profiles_ProfileRepository_h_

#include "Profileinfo.hpp"

NAMESPACE_UPP

class ProfileModel;

/** @class ProfileRepository
    @brief This class is a repository of all the profiles that are available.
 */
class ProfileRepository {
public:
    static ProfileRepository* Get();
    
    virtual ~ProfileRepository();

    void Refresh();
    
    // Profile access
    std::unique_ptr<ProfileInfo>& GetProfile(const String& path);
    bool ProfileExists(const String& path) const;
    
    VectorMap<String, String> GetAllProfiles() const;
    String FindMatchingProfile(ProfileInfo* profile) const;
    
    const String SaveProfile(ProfileInfo* profile, String profile_path = "");
    bool DeleteProfile(const String& path);

private:
    ProfileRepository();
    static std::unique_ptr<ProfileRepository> instance;
    static Mutex mutex;

    VectorMap<String, std::unique_ptr<ProfileInfo>> profiles;
    
    void LoadProfiles();
};

END_UPP_NAMESPACE

#endif
