#ifndef _Editors_ScoreEditor_h_
#define _Editors_ScoreEditor_h_

#include <CtrlLib/CtrlLib.h>
#include <Scores/Scores.h>
#include <ProjectMgmt/ProjectMgmt.h>
#include <FileIO/FileIO.h>
#include <AudioCore/AudioCore.h>

using namespace Upp;

// Forward declarations (until the namespaces are properly included)
namespace Scores {
    class NotationModel;  // Forward declaration for NotationModel
}
namespace ProjectMgmt {
    class CommandManager;  // Forward declaration for CommandManager
}
namespace AudioCore {
    // Forward declaration for MidiPreview (if it exists in AudioCore)
    // If it doesn't exist, I'll need to adjust accordingly
    class Transport;  // Using Transport as a placeholder that likely exists
}

namespace am {

// Forward declarations
class ScoreProjectData;

// Control interface for the Score Editor
class ScoreEditorCtrl : public Ctrl {
public:
    typedef ScoreEditorCtrl CLASSNAME;
    ScoreEditorCtrl();
    
    void SetScoreProject(ScoreProjectData* scoreProject);
    void RefreshDisplay();
    void ZoomIn();
    void ZoomOut();
    
    // Connect to notation document for updates
    void SetNotationDocument(Scores::NotationModel* model);
    
private:
    ScoreProjectData* scoreProject;
    Scores::NotationModel* notationDoc;
    int zoomLevel;
    
    virtual void Paint(Draw& draw);
    virtual void LeftDown(Point p, dword keyflags);
    virtual void MouseMove(Point p, dword keyflags);
    virtual void MouseWheel(Point p, int zdelta, dword keyflags);
};

// Controller/presenter for the Score Editor
class ScoreEditorController {
public:
    ScoreEditorController();
    
    void SetView(ScoreEditorCtrl* view);
    void SetScoreProject(ScoreProjectData* scoreProject);
    void SetProject(am::Project* project);
    
    // Connect to notation document (command manager and midi preview connections may be added later)
    void SetNotationDocument(Scores::NotationModel* doc);
    
    void HandleNoteAdd(int pitch, double start_time, double duration);
    void HandleNoteDelete(int noteIndex);
    void HandleZoomIn();
    void HandleZoomOut();
    void HandleSelectionChanged(const Vector<int>& selectedNotes);
    
private:
    ScoreEditorCtrl* view;
    ScoreProjectData* scoreProject;
    am::Project* project;
    // ProjectMgmt::CommandManager* commandManager;  // Temporarily removed to fix compilation
    // AudioCore::MidiPreview* midiPreview;  // Temporarily removed to fix compilation
    Scores::NotationModel* notationDoc;
};

// Main Score Editor window with toolstrip layout
class ScoreEditor : public TopWindow {
public:
    typedef ScoreEditor CLASSNAME;
    ScoreEditor();
    
    void Open();
    void Close();
    void SetData(void* data);
    
    void Refresh();
    void Save();
    void Load();
    
    // Project file operations with directory management
    bool CreateProject(const String& projectPath);
    bool SaveProject();
    bool LoadProject(const String& projectPath);
    bool SaveProjectAs();
    void DoSaveProjectAs() { SaveProjectAs(); }
    
    // Project directory operations
    String GetProjectDirectory() const;
    String GetAudioDirectory() const;
    String GetCacheDirectory() const;
    String GetBackupDirectory() const;
    
private:
    void InitLayout();
    
    ScoreEditorCtrl scoreCtrl;
    ScoreEditorController controller;
    ToolBar toolBar;
    
    // Project data
    ScoreProjectData* scoreProject;
    String currentProjectPath;
    bool isModified;
    
    void ToolMenu(Bar& bar);
    void Menu(Bar& bar);
    void RefreshContent();
    
    // Callback functions for controller methods
    void HandleZoomInFromController() { controller.HandleZoomIn(); }
    void HandleZoomOutFromController() { controller.HandleZoomOut(); }
    
    // File operations with project directory management
    void NewProject();
    void OpenProject();
    bool SaveProjectInternal();
    void SaveProjectCopy();
    void DoSaveProjectInternal() { SaveProjectInternal(); }
};

}

#endif