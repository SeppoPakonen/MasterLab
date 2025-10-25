# Editors Package

## Overview
The Editors package contains various MIDI and audio editing surfaces including Key Editor, Drum Editor, Score Editor, List Editor, and In-Place Editor. These provide different views and interfaces for editing musical content.

## Key Components

### KeyEditor
- Piano roll style editor for MIDI notes
- Provides time/pitch grid for precise note editing

### DrumEditor
- Drum lane focused editor
- Optimized for percussion and drum pattern editing

### ScoreEditor
- Traditional music notation editor
- Displays content in standard musical notation

### ListEditor
- List view editor for MIDI events
- Provides detailed parameter editing

### InPlaceEditor
- Context-sensitive editor for quick edits
- Small footprint editor for rapid modifications

## Relations to Other Packages
- `CtrlLib`: UI controls and framework for editor windows
- `Draw`: Drawing functionality for custom editor UI
- `AudioCore`: Integration with audio project elements

## Package Classes Relations
- All editors interface with MIDI and audio data from AudioCore
- Editors may communicate with each other through shared data structures
- Each editor type serves a specific workflow need for different types of content