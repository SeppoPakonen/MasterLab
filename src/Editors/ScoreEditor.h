#ifndef _Editors_ScoreEditor_h_
#define _Editors_ScoreEditor_h_

#include <CtrlLib/CtrlLib.h>
#include <Scores/Scores.h>
#include <ProjectMgmt/ProjectMgmt.h>
#include <FileIO/FileIO.h>
#include <AudioCore/AudioCore.h>
#include <AudioCore/MidiPreview.h>

using namespace Upp;

namespace am {

// Forward declarations
class ScoreProjectData;

// Control interface for the Score Editor with toolbar and InfoBar
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
    
    // Toolbar and UI elements
    ToolBar& GetTopToolbar() { return topToolbar; }
    ToolBar& GetToolstrip() { return toolstrip; }
    ToolBar& GetFilterstrip() { return filterstrip; }
    Ctrl& GetInfoBar() { return infoBarCtrl; }
    Ctrl& GetSymbolsPane() { return symbolsPaneCtrl; }
    
    // Info bar management
    void SetInfoBarContent(const String& content);
    String GetInfoBarContent() const { return infoBarContent; }
    
    // Symbols pane management
    void ShowSymbolsPane(bool show = true);
    bool IsSymbolsPaneVisible() const { return symbolsPaneVisible; }
    
    // Selection management
    void SetSelectedNote(int noteIndex);
    int GetSelectedNote() const { return selectedNote; }
    
private:
    ScoreProjectData* scoreProject;
    Scores::NotationModel* notationDoc;
    int zoomLevel;
    
    // UI components
    ToolBar topToolbar;
    ToolBar toolstrip;
    ToolBar filterstrip;
    Ctrl infoBarCtrl;
    Ctrl symbolsPaneCtrl;
    
    // Info bar content
    String infoBarContent;
    int selectedNote;
    bool symbolsPaneVisible;
    
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
    
    // Connect to notation document
    void SetNotationDocument(Scores::NotationModel* doc);
    
    // Connect to command manager for undo/redo and command execution
    void SetCommandManager(ProjectMgmt::CommandManager* cmdMgr);
    ProjectMgmt::CommandManager* GetCommandManager() const { return commandManager; }
    
    // Connect to MIDI preview for auditioning notes
    void SetMidiPreview(AudioCore::MidiPreview* midiPreview);
    AudioCore::MidiPreview* GetMidiPreview() const { return midiPreview; }
    
    void HandleNoteAdd(int pitch, double start_time, double duration);
    void HandleNoteDelete(int noteIndex);
    void HandleZoomIn();
    void HandleZoomOut();
    void HandleSelectionChanged(const Vector<int>& selectedNotes);
    
    // Handle tool selection changes
    void HandleToolChanged(int toolId);
    
    // Handle preview of notes when using mouse over notation
    void HandleNotePreview(int pitch);
    
    // Handle notation document changes
    void HandleNotationChanged();
    
private:
    ScoreEditorCtrl* view;
    ScoreProjectData* scoreProject;
    am::Project* project;
    ProjectMgmt::CommandManager* commandManager;
    AudioCore::MidiPreview* midiPreview;
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
    
    // Connect to external systems
    void ConnectToCommandManager();
    void ConnectToMidiPreview();
    
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