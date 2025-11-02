#include "ScoreProject.h"
#include <FileIO/FileIO.h>

namespace am {

ScoreProjectData::ScoreProjectData() {
    // Initialize with default values
    title = "Untitled Score";
    composer = "Unknown";
}

String ScoreProjectData::GetAudioDirectory() const {
    if (!projectDirectory.IsEmpty()) {
        return AppendFileName(projectDirectory, "Audio");
    }
    return "Audio";
}

String ScoreProjectData::GetCacheDirectory() const {
    if (!projectDirectory.IsEmpty()) {
        return AppendFileName(projectDirectory, "Cache");
    }
    return "Cache";
}

String ScoreProjectData::GetBackupDirectory() const {
    if (!projectDirectory.IsEmpty()) {
        return AppendFileName(projectDirectory, "Backup");
    }
    return "Backup";
}

bool ScoreProjectData::CreateProject(const String& projectPath) {
    // Set project path information
    this->projectPath = projectPath;
    this->projectDirectory = GetFileDirectory(projectPath);
    this->projectName = GetFileTitle(projectPath);
    this->isLibrary = false;
    
    // Create project directories
    if (!CreateProjectDirectories()) {
        return false;
    }
    
    // Clear any existing data
    Clear();
    
    // Set default title
    title = projectName;
    
    isModified = false;
    return true;
}

bool ScoreProjectData::SaveProject() {
    if (projectPath.IsEmpty()) {
        return false;
    }
    
    try {
        // For now, we'll save a simple placeholder
        String jsonStr = "{\n  \"title\": \"" + title + "\",\n  \"composer\": \"" + composer + "\"\n}";
        
        // Write to file
        FileOut out(projectPath);
        if (!out) {
            return false;
        }
        out << jsonStr;
        out.Close();
        
        isModified = false;
        return true;
    }
    catch (...) {
        return false;
    }
}

bool ScoreProjectData::LoadProject(const String& projectPath) {
    try {
        // Set project path information
        this->projectPath = projectPath;
        this->projectDirectory = GetFileDirectory(projectPath);
        this->projectName = GetFileTitle(projectPath);
        this->isLibrary = false;
        
        // Validate project structure
        if (!ValidateProjectStructure()) {
            return false;
        }
        
        // For now, we'll just load a simple placeholder
        String jsonStr = LoadFile(projectPath);
        if (jsonStr.IsEmpty()) {
            return false;
        }
        
        // In a real implementation, we would parse the JSON and deserialize the data
        // For now, we'll just set some default values
        title = projectName;
        composer = "Unknown";
        
        isModified = false;
        return true;
    }
    catch (...) {
        return false;
    }
}

bool ScoreProjectData::SaveProjectAs(const String& newPath) {
    // Update project path information
    String oldPath = projectPath;
    projectPath = newPath;
    projectDirectory = GetFileDirectory(newPath);
    projectName = GetFileTitle(newPath);
    isLibrary = false;
    
    // Try to save
    if (!SaveProject()) {
        // Restore old path on failure
        projectPath = oldPath;
        projectDirectory = GetFileDirectory(oldPath);
        projectName = GetFileTitle(oldPath);
        return false;
    }
    
    return true;
}

bool ScoreProjectData::CreateLibrary(const String& libraryPath) {
    // Set library path information
    this->libraryPath = libraryPath;
    this->projectPath = libraryPath;  // For consistency
    this->projectDirectory = GetFileDirectory(libraryPath);
    this->projectName = GetFileTitle(libraryPath);
    this->isLibrary = true;
    
    // Clear any existing data
    Clear();
    
    // Set default title
    title = projectName;
    
    isModified = false;
    return true;
}

bool ScoreProjectData::SaveLibrary() {
    if (libraryPath.IsEmpty()) {
        return false;
    }
    
    try {
        // For now, we'll save a simple placeholder
        String jsonStr = "{\n  \"title\": \"" + title + "\",\n  \"composer\": \"" + composer + "\",\n  \"isLibrary\": true\n}";
        
        // Write to file
        FileOut out(libraryPath);
        if (!out) {
            return false;
        }
        out << jsonStr;
        out.Close();
        
        isModified = false;
        return true;
    }
    catch (...) {
        return false;
    }
}

bool ScoreProjectData::LoadLibrary(const String& libraryPath) {
    try {
        // Set library path information
        this->libraryPath = libraryPath;
        this->projectPath = libraryPath;  // For consistency
        this->projectDirectory = GetFileDirectory(libraryPath);
        this->projectName = GetFileTitle(libraryPath);
        this->isLibrary = true;
        
        // For now, we'll just load a simple placeholder
        String jsonStr = LoadFile(libraryPath);
        if (jsonStr.IsEmpty()) {
            return false;
        }
        
        // In a real implementation, we would parse the JSON and deserialize the data
        // For now, we'll just set some default values
        title = projectName;
        composer = "Unknown";
        
        isModified = false;
        return true;
    }
    catch (...) {
        return false;
    }
}

bool ScoreProjectData::SaveLibraryAs(const String& newPath) {
    // Update library path information
    String oldPath = libraryPath;
    libraryPath = newPath;
    projectPath = newPath;  // For consistency
    projectDirectory = GetFileDirectory(newPath);
    projectName = GetFileTitle(newPath);
    
    // Try to save
    if (!SaveLibrary()) {
        // Restore old path on failure
        libraryPath = oldPath;
        projectPath = oldPath;  // For consistency
        projectDirectory = GetFileDirectory(oldPath);
        projectName = GetFileTitle(oldPath);
        return false;
    }
    
    return true;
}

bool ScoreProjectData::CreateProjectDirectories() {
    if (projectDirectory.IsEmpty()) {
        return false;
    }
    
    // Create main project directory
    if (!DirectoryExists(projectDirectory)) {
        if (!RealizeDirectory(projectDirectory)) {
            return false;
        }
    }
    
    // Create Audio directory
    String audioDir = GetAudioDirectory();
    if (!DirectoryExists(audioDir)) {
        if (!RealizeDirectory(audioDir)) {
            return false;
        }
    }
    
    // Create Cache directory
    String cacheDir = GetCacheDirectory();
    if (!DirectoryExists(cacheDir)) {
        if (!RealizeDirectory(cacheDir)) {
            return false;
        }
    }
    
    // Create Backup directory
    String backupDir = GetBackupDirectory();
    if (!DirectoryExists(backupDir)) {
        if (!RealizeDirectory(backupDir)) {
            return false;
        }
    }
    
    return true;
}

bool ScoreProjectData::ValidateProjectStructure() {
    if (projectDirectory.IsEmpty()) {
        return false;
    }
    
    // Check if project directory exists
    if (!DirectoryExists(projectDirectory)) {
        return false;
    }
    
    // Check if Audio directory exists (create if missing)
    String audioDir = GetAudioDirectory();
    if (!DirectoryExists(audioDir)) {
        if (!RealizeDirectory(audioDir)) {
            return false;
        }
    }
    
    // Check if Cache directory exists (create if missing)
    String cacheDir = GetCacheDirectory();
    if (!DirectoryExists(cacheDir)) {
        if (!RealizeDirectory(cacheDir)) {
            return false;
        }
    }
    
    // Check if Backup directory exists (create if missing)
    String backupDir = GetBackupDirectory();
    if (!DirectoryExists(backupDir)) {
        if (!RealizeDirectory(backupDir)) {
            return false;
        }
    }
    
    return true;
}

void ScoreProjectData::Jsonize(JsonIO& jio) {
    jio
    ("notationModel", notationModel)
    ("displaySettings.zoomFactor", displaySettings.zoomFactor)
    ("displaySettings.showMeasureNumbers", displaySettings.showMeasureNumbers)
    ("displaySettings.showTimeSignatures", displaySettings.showTimeSignatures)
    ("displaySettings.showKeySignatures", displaySettings.showKeySignatures)
    ("displaySettings.showClefs", displaySettings.showClefs)
    ("displaySettings.showNoteNames", displaySettings.showNoteNames)
    ("displaySettings.fontSize", displaySettings.fontSize)
    ("displaySettings.backgroundColor", displaySettings.backgroundColor)
    ("displaySettings.noteColor", displaySettings.noteColor)
    ("renderingSettings.enableAntialiasing", renderingSettings.enableAntialiasing)
    ("renderingSettings.highQualityRendering", renderingSettings.highQualityRendering)
    ("renderingSettings.lineThickness", renderingSettings.lineThickness)
    ("title", title)
    ("composer", composer)
    ("arranger", arranger)
    ("lyricist", lyricist)
    ("copyright", copyright)
    ("comments", comments)
    ("libraryPath", libraryPath)
    ("isLibrary", isLibrary);
}

void ScoreProjectData::Clear() {
    notationModel.Clear();
    title = "Untitled Score";
    composer = "Unknown";
    arranger = "";
    lyricist = "";
    copyright = "";
    comments = "";
    libraryPath = "";
    isLibrary = false;
    
    isModified = false;
}

void ScoreProjectData::SetTitle(const String& newTitle) {
    title = newTitle;
    isModified = true;
}

}