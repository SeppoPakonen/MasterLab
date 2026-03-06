/*
SPDX-FileCopyrightText: 2014 Till Theato <root@ttill.de>
SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_MltConnection_h_
#define _Cool_MltConnection_h_

#include <Core/Core.h>

NAMESPACE_UPP

namespace Mlt {
    class Repository;
}

class MltConnection {
public:
    // Singleton management
    static void Construct(const String& mlt_path);
    static MltConnection& Self();
    
    // MLT accessors
    std::unique_ptr<Mlt::Repository>& GetMltRepository() { return repository; }
    
    // Logic
    static void RefreshLumas();

protected:
    MltConnection(const String& mlt_path);
    
    void LocateMeltAndProfilesPath(const String& mlt_path = "");

private:
    static std::unique_ptr<MltConnection> instance;
    std::unique_ptr<Mlt::Repository> repository;
};

END_UPP_NAMESPACE

#endif
