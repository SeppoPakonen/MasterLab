/*
    SPDX-FileCopyrightText: 2016 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_library_LibraryWidget_h_
#define _Cool_library_LibraryWidget_h_

#include <CtrlLib/CtrlLib.h>
#include "../Definitions.h"

NAMESPACE_UPP

class ProjectManager;

class LibraryWidget : public ParentCtrl {
public:
    typedef LibraryWidget CLASSNAME;

    LibraryWidget(ProjectManager* manager, MainWindow* parent = nullptr);
    virtual ~LibraryWidget();

    void SetupActions();
    void RefreshLibrary();

    // Logic
    void AddToProject();
    void DeleteFromLibrary();
    void AddFolder();

protected:
    virtual void Layout() override;

private:
    ProjectManager* project_manager;
    
    // U++ UI Components
    TreeCtrl   library_tree;
    ToolBar    tool_bar;
    ProgressIndicator progress_bar;
    
    void BuildUI();
    void OnItemEdited(int id);
};

END_UPP_NAMESPACE

#endif
