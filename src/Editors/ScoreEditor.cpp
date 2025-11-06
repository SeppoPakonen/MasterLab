#include "ScoreEditor.h"
#include <Scores/LayoutEngine.h>
#include <Scores/NotationModel.h>  // Include full NotationModel definition for implementation
#include <ProjectMgmt/Commands.h>  // Include CommandManager
#include <AudioCore/MidiPreview.h>  // Include MidiPreview
#include <CtrlLib/CtrlLib.h>

namespace am {

// ScoreEditorCtrl implementation
ScoreEditorCtrl::ScoreEditorCtrl() : scoreProject(nullptr), notationDoc(nullptr), zoomLevel(100),
                                     selectedNote(-1), symbolsPaneVisible(false) {
    // Initialize the score control
    infoBarCtrl.SetFrame(BlackFrame());
    infoBarCtrl.SetRect(0, 0, GetSize().cx, 20);  // Black info bar at top
    infoBarCtrl.SetBgColor(Black());
    
    symbolsPaneCtrl.SetFrame(BlackFrame());
    symbolsPaneCtrl.SetRect(0, 0, 50, GetSize().cy);  // Left symbols pane
}

void ScoreEditorCtrl::SetScoreProject(ScoreProjectData* scoreProject) {
    this->scoreProject = scoreProject;
    RefreshDisplay();
}

void ScoreEditorCtrl::SetNotationDocument(Scores::NotationModel* doc) {
    this->notationDoc = doc;
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

void ScoreEditorCtrl::SetInfoBarContent(const String& content) {
    infoBarContent = content;
    infoBarCtrl.Refresh();
}

void ScoreEditorCtrl::ShowSymbolsPane(bool show) {
    symbolsPaneVisible = show;
    Refresh();
}

void ScoreEditorCtrl::SetSelectedNote(int noteIndex) {
    selectedNote = noteIndex;
    
    // Update info bar with details about the selected note
    if (scoreProject && selectedNote >= 0) {
        const Vector<Measure>& measures = scoreProject->GetNotationModel().GetMeasures();
        // Find the note and update the info bar with its details
        int tempNoteIdx = 0;
        for (const Measure& measure : measures) {
            for (const Note& note : measure.notes) {
                if (tempNoteIdx == selectedNote) {
                    String noteInfo = "Pitch: " + IntStr(note.pitch) + 
                                     " | Start: " + DoubleStr(note.start_time, 3) +
                                     " | Duration: " + DoubleStr(note.duration, 3);
                    SetInfoBarContent(noteInfo);
                    break;
                }
                tempNoteIdx++;
            }
        }
    }
}

void ScoreEditorCtrl::Paint(Draw& draw) {
    // Paint the score notation
    draw.DrawRect(GetSize(), White());
    
    if (!scoreProject) return;
    
    // Draw symbols pane if visible
    if (symbolsPaneVisible) {
        draw.DrawRect(0, 0, 50, GetSize().cy, Gray());
    }
    
    // Draw the main notation area
    int notationStartX = symbolsPaneVisible ? 50 : 0;
    int notationWidth = GetSize().cx - notationStartX;
    
    const Vector<Measure>& measures = scoreProject->GetNotationModel().GetMeasures();
    int yPos = 50;
    int xPos = notationStartX + 50;
    
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
                // Draw note - highlight if it's the selected note
                Color noteColor = (selectedNote >= 0 && 
                                  GetNoteIndexAtPosition(Point(noteX, noteY)) == selectedNote) ? 
                                  Red() : Black();
                draw.DrawEllipse(noteX - 5, noteY - 5, 10, 10, noteColor);
            }
        }
        
        xPos += 150; // Move to next measure
    }
    
    // Draw staff lines
    for (int i = 0; i < 5; i++) {
        int y = 150 - i * 10;
        draw.DrawLine(notationStartX + 20, y, notationStartX + notationWidth - 20, y, 1, Black());
    }
    
    // Draw info bar content
    if (!infoBarContent.IsEmpty()) {
        draw.DrawText(notationStartX + 10, 5, infoBarContent, StdFont(10), White());
    }
}

void ScoreEditorCtrl::LeftDown(Point p, dword keyflags) {
    // Check if the click was on a note
    int noteIndex = GetNoteIndexAtPosition(p);
    
    if (noteIndex >= 0) {
        // A note was clicked - select it
        SetSelectedNote(noteIndex);
        Refresh();
    } else {
        // Empty space was clicked - clear selection
        SetSelectedNote(-1);
        Refresh();
    }
}

void ScoreEditorCtrl::MouseMove(Point p, dword keyflags) {
    // Handle mouse movement over notes
    if (HasMouseIn()) {
        // For now, just update the cursor
        int noteIndex = GetNoteIndexAtPosition(p);
        if (noteIndex >= 0) {
            SetCursor(Cursor::arrow);
        } else {
            SetCursor(Cursor::arrow);
        }
    }
}

void ScoreEditorCtrl::MouseWheel(Point p, int zdelta, dword keyflags) {
    if (zdelta > 0) {
        ZoomIn();
    } else {
        ZoomOut();
    }
}

int ScoreEditorCtrl::GetNoteIndexAtPosition(Point p) {
    if (!scoreProject) return -1;
    
    int notationStartX = symbolsPaneVisible ? 50 : 0;
    const Vector<Measure>& measures = scoreProject->GetNotationModel().GetMeasures();
    int yPos = 50;
    int xPos = notationStartX + 50;
    int noteIndex = 0;
    
    for (int i = 0; i < measures.GetCount(); i++) {
        const Measure& measure = measures[i];
        // Check notes in this measure
        for (const Note& note : measure.notes) {
            int noteX = xPos + (int)(note.start_time * 10);
            int noteY = 200 - (note.pitch % 12) * 10;
            
            // Simple hit detection (within 10 pixels)
            if (abs(p.x - noteX) < 10 && abs(p.y - noteY) < 10) {
                return noteIndex;
            }
            noteIndex++;
        }
        xPos += 150; // Move to next measure
    }
    
    return -1; // No note at this position
}

// ScoreEditorController implementation
ScoreEditorController::ScoreEditorController() : view(nullptr), scoreProject(nullptr), 
                                                 project(nullptr), commandManager(nullptr),
                                                 midiPreview(nullptr), notationDoc(nullptr) {
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

void ScoreEditorController::SetNotationDocument(Scores::NotationModel* doc) {
    this->notationDoc = doc;
    if (view) {
        view->SetNotationDocument(doc);
    }
}

void ScoreEditorController::SetCommandManager(ProjectMgmt::CommandManager* cmdMgr) {
    this->commandManager = cmdMgr;
}

void ScoreEditorController::SetMidiPreview(AudioCore::MidiPreview* midiPreview) {
    this->midiPreview = midiPreview;
}

void ScoreEditorController::HandleNoteAdd(int pitch, double start_time, double duration) {
    if (!scoreProject || !project) return;
    
    // In a real implementation, we would create a command to add the note
    // and execute it through the command manager
    // For now, this is a placeholder implementation
}

void ScoreEditorController::HandleNoteDelete(int noteIndex) {
    if (!scoreProject || !project) return;
    
    // In a real implementation, we would create a command to delete the note
    // and execute it through the command manager
    // For now, this is a placeholder implementation
}

void ScoreEditorController::HandleZoomIn() {
    if (view) view->ZoomIn();
}

void ScoreEditorController::HandleZoomOut() {
    if (view) view->ZoomOut();
}

void ScoreEditorController::HandleSelectionChanged(const Vector<int>& selectedNotes) {
    // Handle when notes are selected in the UI
    // This might trigger updates in other connected components
    if (view && selectedNotes.GetCount() > 0) {
        view->SetSelectedNote(selectedNotes[0]);  // Take the first selected note
        view->RefreshDisplay();
    }
}

void ScoreEditorController::HandleToolChanged(int toolId) {
    // Handle changes in the selected tool
    // In a real implementation, this would affect the behavior of different tools
}

void ScoreEditorController::HandleNotePreview(int pitch) {
    // Preview the note using MIDI preview if available
    if (midiPreview) {
        midiPreview->PreviewNote(pitch, 100, 500);  // Preview with velocity 100 for 500ms
    }
}

void ScoreEditorController::HandleNotationChanged() {
    // Handle when the notation document has been modified
    // This might trigger updates to linked views
    if (view) {
        view->RefreshDisplay();
    }
}

// ScoreEditor implementation
ScoreEditor::ScoreEditor() : scoreProject(nullptr), isModified(false) {
    Title("Score Editor");
    Size(1000, 700);
    InitLayout();
}

void ScoreEditor::InitLayout() {
    // Add the tool bars as frames
    AddFrame(scoreCtrl.GetTopToolbar());  // Top toolbar
    Add(scoreCtrl);
    
    // Connect the controller
    controller.SetView(&scoreCtrl);
    
    // Connect to external systems
    ConnectToCommandManager();
    ConnectToMidiPreview();
}

void ScoreEditor::ConnectToCommandManager() {
    // Get the global command manager (in a real implementation, this would be properly initialized)
    // For now, we'll create a temporary one
    static ProjectMgmt::CommandManager globalCommandManager;
    controller.SetCommandManager(&globalCommandManager);
}

void ScoreEditor::ConnectToMidiPreview() {
    // Get the global MIDI preview system (in a real implementation, this would be properly initialized)
    // For now, we'll create a temporary one
    static AudioCore::MidiPreview globalMidiPreview;
    controller.SetMidiPreview(&globalMidiPreview);
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
    bar.Add("Show Symbols", CtrlImg::folder(), [this]() { scoreCtrl.ShowSymbolsPane(true); });
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
        b.Add("Show/Hide Symbols Pane", [this]() { 
            scoreCtrl.ShowSymbolsPane(!scoreCtrl.IsSymbolsPaneVisible()); 
        });
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
    // Set the project data and connect to the ProjectMgmt::CommandManager
    ScoreProjectData* scoreProject = reinterpret_cast<ScoreProjectData*>(data);
    controller.SetScoreProject(scoreProject);
    controller.SetNotationDocument(&scoreProject->GetNotationModel());
    
    // Connect to external systems if not already done
    ConnectToCommandManager();
    ConnectToMidiPreview();
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
        
        // Connect the notation document to the controller
        controller.SetNotationDocument(&scoreProject->GetNotationModel());
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
            
            // Connect the notation document to the controller
            controller.SetNotationDocument(&scoreProject->GetNotationModel());
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
            
            // Connect the notation document to the controller
            controller.SetNotationDocument(&scoreProject->GetNotationModel());
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