/*
    SPDX-FileCopyrightText: 2012 Till Theato <root@ttill.de>
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_bin_MediaBrowser_h_
#define _Cool_bin_MediaBrowser_h_

#include <CtrlLib/CtrlLib.h>
#include "../Definitions.h"

NAMESPACE_UPP

class MainWindow;

class MediaBrowser : public ParentCtrl {
public:
    typedef MediaBrowser CLASSNAME;

    MediaBrowser(MainWindow* parent = nullptr);
    virtual ~MediaBrowser();

    void SetRootPath(const String& path);
    String GetCurrentPath() const { return current_path; }

    // Event handlers
    void OnFileSelected();
    void OnDirectoryChanged();

protected:
    virtual void Layout() override;

private:
    String current_path;
    
    // U++ File browsing components
    TreeCtrl   dir_tree;
    FileList   file_list;
    Splitter   splitter;
    
    void BuildUI();
    void ScanDirectory(const String& path);
};

END_UPP_NAMESPACE

#endif
