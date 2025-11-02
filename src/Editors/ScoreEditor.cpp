#include "ScoreEditor.h"
#include <Scores/LayoutEngine.h>
#include <CtrlLib/CtrlLib.h>

namespace am {

// ScoreEditorCtrl implementation
ScoreEditorCtrl::ScoreEditorCtrl() : scoreProject(nullptr), zoomLevel(100) {
    // Initialize the score control
}

void ScoreEditorCtrl::SetScoreProject(ScoreProjectData* scoreProject) {
    this->scoreProject = scoreProject;
    RefreshDisplay();
}

void ScoreEditorCtrl::RefreshDisplay() {
    Refresh();
}

void ScoreEditorCtrl::ZoomIn() {
    zoomLevel = min(200, zoomLevel + 10);
    Refresh();
}

void ScoreEditorCtrl::ZoomOut() {
    zoomLevel = max(50, zoomLevel - 10);
    Refresh();
}

void ScoreEditorCtrl::Paint(Draw& draw) {
    // Paint the score notation
    draw.DrawRect(GetSize(), White());
    
    if (!scoreProject) return;
    
    const Vector<Measure>& measures = scoreProject->GetNotationModel().GetMeasures();
    int yPos = 50;
    int xPos = 50;
    
    for (int i = 0; i < measures.GetCount(); i++) {
        const Measure& measure = measures[i];
        // Draw measure line
        draw.DrawLine(xPos, 30, xPos, 250, 1, Black());
        
        // Draw notes
        for (const Note& note : measure.notes) {
            int noteX = xPos + (int)(note.start_time * 10);
            int noteY = 200 - (note.pitch % 12) * 10;  // Simplified mapping
            
            if (note.is_rest) {
                // Draw rest
                draw.DrawText(noteX, noteY, "r", StdFont(10));
            } else {
                // Draw note
                draw.DrawEllipse(noteX - 5, noteY - 5, 10, 10, Black());
            }
        }
        
        xPos += 150; // Move to next measure
    }
    
    // Draw staff lines
    for (int i = 0; i < 5; i++) {
        int y = 150 - i * 10;
        draw.DrawLine(20, y, GetSize().cx - 20, y, 1, Black());
    }
}

void ScoreEditorCtrl::LeftDown(Point p, dword keyflags) {
    // Handle note placement
}

void ScoreEditorCtrl::MouseMove(Point p, dword keyflags) {
    // Handle mouse movement over notes
    if (HasMouseIn()) {
        // Update cursor based on position
    }
}

// ScoreEditorController implementation
ScoreEditorController::ScoreEditorController() : view(nullptr), scoreProject(nullptr), project(nullptr) {
    // Initialize the controller
}

void ScoreEditorController::SetView(ScoreEditorCtrl* view) {
    this->view = view;
}

void ScoreEditorController::SetScoreProject(ScoreProjectData* scoreProject) {
    this->scoreProject = scoreProject;
    if (view) {
        view->SetScoreProject(scoreProject);
    }
}

void ScoreEditorController::SetProject(am::Project* project) {
    this->project = project;
}

void ScoreEditorController::HandleNoteAdd(int pitch, double start_time, double duration) {
    if (!scoreProject || !project) return;
    
    // This would be a more complex implementation in a real system
    // For now, we'll just add a note to the first measure if it exists
    if (scoreProject->GetNotationModel().GetMeasures().GetCount() > 0) {
        // In a real implementation, we would use the project's command system
    }
}

void ScoreEditorController::HandleNoteDelete(int noteIndex) {
    if (!scoreProject || !project) return;
    
    // In a real implementation, we would use the project's command system
}

void ScoreEditorController::HandleZoomIn() {
    if (view) view->ZoomIn();
}

void ScoreEditorController::HandleZoomOut() {
    if (view) view->ZoomOut();
}

// ScoreEditor implementation
ScoreEditor::ScoreEditor() : scoreProject(nullptr), isModified(false) {
    Title("Score Editor");
    Size(800, 600);
    InitLayout();
}

void ScoreEditor::InitLayout() {
    // Add the tool bar
    AddFrame(toolBar);
    toolBar.Set(THISBACK(ToolMenu));
    
    // Add the score control
    Add(scoreCtrl);
    
    // Connect the controller
    controller.SetView(&scoreCtrl);
    
    // Connect to command manager if available
    // In a real implementation, this would connect to ProjectMgmt::CommandManager
}

void ScoreEditor::ToolMenu(Bar& bar) {
    bar.Add("New", CtrlImg::new_doc(), THISBACK(NewProject));
    bar.Add("Open", CtrlImg::open(), THISBACK(OpenProject));
    bar.Add("Save", CtrlImg::save(), THISBACK(DoSaveProjectInternal));
    bar.Add("Save As", CtrlImg::save_as(), THISBACK(DoSaveProjectAs));
    bar.Separator();
    bar.Add("Zoom In", CtrlImg::plus(), THISBACK(HandleZoomInFromController));
    bar.Add("Zoom Out", CtrlImg::minus(), THISBACK(HandleZoomOutFromController));
    bar.Add("Refresh", CtrlImg::redo(), THISBACK(Refresh));
}

void ScoreEditor::Menu(Bar& bar) {
    bar.Sub("File", [=](Bar& b) {
        b.Add("New Project", THISBACK(NewProject));
        b.Add("Open Project", THISBACK(OpenProject));
        b.Add("Save Project", THISBACK(DoSaveProjectInternal));
        b.Add("Save Project As", THISBACK(DoSaveProjectAs));
        b.Separator();
        b.Add("Close", THISBACK(Close));
    });
    
    bar.Sub("Edit", [=](Bar& b) {
        b.Add("Undo", THISBACK(Refresh));
        b.Add("Redo", THISBACK(Refresh));
        b.Separator();
        b.Add("Cut", THISBACK(Refresh));
        b.Add("Copy", THISBACK(Refresh));
        b.Add("Paste", THISBACK(Refresh));
    });
    
    bar.Sub("View", [=](Bar& b) {
        b.Add("Zoom In", THISBACK(HandleZoomInFromController));
        b.Add("Zoom Out", THISBACK(HandleZoomOutFromController));
        b.Add("Actual Size", THISBACK(Refresh));
    });
}

void ScoreEditor::Open() {
    // Open the editor
    ActiveFocus(scoreCtrl);
}

void ScoreEditor::Close() {
    // Close the editor
    TopWindow::Close();
}

void ScoreEditor::SetData(void* data) {
    // In a real implementation, this would set the project data
    // and connect to the ProjectMgmt::CommandManager
    ScoreProjectData* scoreProject = reinterpret_cast<ScoreProjectData*>(data);
    controller.SetScoreProject(scoreProject);
}

void ScoreEditor::Refresh() {
    scoreCtrl.RefreshDisplay();
}

void ScoreEditor::Save() {
    // In a real implementation, this would use the FileIO package
    SaveProjectInternal();
}

void ScoreEditor::Load() {
    // In a real implementation, this would use the FileIO package
    OpenProject();
}

String ScoreEditor::GetProjectDirectory() const {
    if (scoreProject) {
        return scoreProject->GetProjectDirectory();
    }
    return ".";
}

String ScoreEditor::GetAudioDirectory() const {
    if (scoreProject) {
        return scoreProject->GetAudioDirectory();
    }
    return "./Audio";
}

String ScoreEditor::GetCacheDirectory() const {
    if (scoreProject) {
        return scoreProject->GetCacheDirectory();
    }
    return "./Cache";
}

String ScoreEditor::GetBackupDirectory() const {
    if (scoreProject) {
        return scoreProject->GetBackupDirectory();
    }
    return "./Backup";
}

bool ScoreEditor::CreateProject(const String& projectPath) {
    if (!scoreProject) {
        scoreProject = new ScoreProjectData();
    }
    
    return scoreProject->CreateProject(projectPath);
}

bool ScoreEditor::SaveProject() {
    if (!scoreProject) {
        scoreProject = new ScoreProjectData();
    }
    
    return scoreProject->SaveProject();
}

bool ScoreEditor::LoadProject(const String& projectPath) {
    if (!scoreProject) {
        scoreProject = new ScoreProjectData();
    }
    
    bool result = scoreProject->LoadProject(projectPath);
    if (result) {
        currentProjectPath = projectPath;
        isModified = false;
        Refresh();
    }
    return result;
}

bool ScoreEditor::SaveProjectAs() {
    FileSel fs;
    fs.Type("Score Project", "*.scp");
    if (fs.ExecuteSaveAs()) {
        String newPath = fs.Get();
        if (!scoreProject) {
            scoreProject = new ScoreProjectData();
        }
        bool result = scoreProject->SaveProjectAs(newPath);
        if (result) {
            currentProjectPath = newPath;
            isModified = false;
            PromptOK("Project saved successfully!");
        } else {
            PromptOK("Failed to save project!");
        }
        return result;
    }
    return false;
}

void ScoreEditor::NewProject() {
    FileSel fs;
    fs.Type("Score Project", "*.scp");
    if (fs.ExecuteSaveAs()) {
        String projectPath = fs.Get();
        if (!scoreProject) {
            scoreProject = new ScoreProjectData();
        }
        
        if (scoreProject->CreateProject(projectPath)) {
            currentProjectPath = projectPath;
            isModified = false;
            Refresh();
            PromptOK("New project created successfully!");
        } else {
            PromptOK("Failed to create new project!");
        }
    }
}

void ScoreEditor::OpenProject() {
    FileSel fs;
    fs.Type("Score Project", "*.scp");
    if (fs.ExecuteOpen()) {
        String projectPath = fs.Get();
        if (!scoreProject) {
            scoreProject = new ScoreProjectData();
        }
        
        if (scoreProject->LoadProject(projectPath)) {
            currentProjectPath = projectPath;
            isModified = false;
            Refresh();
            PromptOK("Project loaded successfully!");
        } else {
            PromptOK("Failed to load project!");
        }
    }
}

bool ScoreEditor::SaveProjectInternal() {
    if (!scoreProject) {
        return false;
    }
    
    if (currentProjectPath.IsEmpty()) {
        return SaveProjectAs();
    } else {
        bool result = scoreProject->SaveProject();
        if (result) {
            isModified = false;
            PromptOK("Project saved successfully!");
        } else {
            PromptOK("Failed to save project!");
        }
        return result;
    }
}

}