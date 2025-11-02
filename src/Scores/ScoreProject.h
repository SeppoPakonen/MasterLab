#ifndef _Scores_ScoreProject_h_
#define _Scores_ScoreProject_h_

#include <Core/Core.h>
#include <FileIO/FileIO.h>
#include "NotationModel.h"

using namespace Upp;

namespace am {

// Datamodel for score-specific project data
class ScoreProjectData {
public:
    ScoreProjectData();
    
    // Score content
    NotationModel notationModel;
    
    // Score display settings
    struct DisplaySettings {
        double zoomFactor = 1.0;
        bool showMeasureNumbers = true;
        bool showTimeSignatures = true;
        bool showKeySignatures = true;
        bool showClefs = true;
        bool showNoteNames = false;
        int fontSize = 12;
        Color backgroundColor = White;
        Color noteColor = Black;
        
        void Jsonize(JsonIO& jio) {
            jio
            ("zoomFactor", zoomFactor)
            ("showMeasureNumbers", showMeasureNumbers)
            ("showTimeSignatures", showTimeSignatures)
            ("showKeySignatures", showKeySignatures)
            ("showClefs", showClefs)
            ("showNoteNames", showNoteNames)
            ("fontSize", fontSize)
            ("backgroundColor", backgroundColor)
            ("noteColor", noteColor);
        }
    } displaySettings;
    
    // Score rendering settings
    struct RenderingSettings {
        bool enableAntialiasing = true;
        bool highQualityRendering = true;
        double lineThickness = 1.0;
        
        void Jsonize(JsonIO& jio) {
            jio
            ("enableAntialiasing", enableAntialiasing)
            ("highQualityRendering", highQualityRendering)
            ("lineThickness", lineThickness);
        }
    } renderingSettings;
    
    // Score metadata
    String title;
    String composer;
    String arranger;
    String lyricist;
    String copyright;
    String comments;
    
    // Library file support
    String libraryPath;           // Path to separate library file (when used as library)
    bool isLibrary = false;       // Whether this is a library file
    
    // Project directory management
    String projectPath;           // Full path to .scp file
    String projectDirectory;      // Directory containing the project
    String projectName;          // Name of the project (without extension)
    
    // Directory structure management
    String GetProjectDirectory() const { return projectDirectory; }
    String GetAudioDirectory() const;    // ./Audio subdirectory
    String GetCacheDirectory() const;    // ./Cache subdirectory
    String GetBackupDirectory() const;   // ./Backup subdirectory
    
    // Project file operations
    bool CreateProject(const String& projectPath);
    bool SaveProject();
    bool LoadProject(const String& projectPath);
    bool SaveProjectAs(const String& newPath);
    
    // Library file operations
    bool CreateLibrary(const String& libraryPath);
    bool SaveLibrary();
    bool LoadLibrary(const String& libraryPath);
    bool SaveLibraryAs(const String& newPath);
    
    // Directory management
    bool CreateProjectDirectories();
    bool ValidateProjectStructure();
    
    // Serialization methods
    void Jsonize(JsonIO& jio);
    
    // Additional methods
    void Clear();
    void SetTitle(const String& title);
    String GetTitle() const { return title; }
    
    // Accessors
    NotationModel& GetNotationModel() { return notationModel; }
    const NotationModel& GetNotationModel() const { return notationModel; }
    
    bool IsModified() const { return isModified; }
    void SetModified(bool modified) { isModified = modified; }
    
    bool IsLibraryFile() const { return isLibrary; }
    String GetLibraryPath() const { return libraryPath; }
    
private:
    bool isModified = false;
};

}

#endif