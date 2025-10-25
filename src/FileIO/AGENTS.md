# FileIO Package

## Overview
The FileIO package handles all file input/output operations including project loading/saving, media import/export, recent files management, backup functionality, and project templates. It serves as the central hub for all file-related operations in the application.

## Key Components

### Import
- Handles importing various media formats into the project
- Supports audio, MIDI, video, MusicXML, OMF, and other formats

### Export
- Handles exporting project content in various formats
- Supports audio mixdowns, MIDI files, MusicXML, OMF, and other formats

### MediaFormatRegistry
- Manages information about supported media formats
- Tracks which formats can be imported/exported

### RecentFiles
- Maintains list of recently opened projects
- Provides access to recent file history

### Backup
- Handles project backup functionality
- Manages backup creation and rotation

### Templates
- Manages project templates
- Handles template instantiation and creation

## Relations to Other Packages
- `Core`: Basic U++ framework functionality
- `CtrlCore`, `CtrlLib`: UI controls and framework for file dialogs
- `AudioCore`: Audio project elements that need import/export
- `AudioFX`: Audio effects that may be part of import/export
- `AudioGraph`: Audio routing that may be part of import/export

## Package Classes Relations
- Import and Export classes interface with MediaFormatRegistry to determine supported formats
- RecentFiles provides file history to UI components
- Backup works with project files to maintain safe copies
- Templates provide project starting points to the application