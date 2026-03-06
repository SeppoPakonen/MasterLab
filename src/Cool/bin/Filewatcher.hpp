/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_bin_FileWatcher_h_
#define _Cool_bin_FileWatcher_h_

#include "../Definitions.h"

NAMESPACE_UPP

/** @class FileWatcher
    @brief This class is a wrapper around U++ file monitoring capabilities.
 */
class FileWatcher {
public:
    FileWatcher();
    virtual ~FileWatcher();

    void AddFile(const String& path);
    void RemoveFile(const String& path);
    void Clear();

private:
    Vector<String> watched_files;
};

END_UPP_NAMESPACE

#endif
