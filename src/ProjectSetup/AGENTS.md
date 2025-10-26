# ProjectSetup Package

## Overview
Implements the Cubase 5 style Project Setup modal dialog.  The package provides a reusable `ProjectSetupDialog` with data bindings for timing formats, sample rate, record format, and pan law.  It bridges configuration between `ProjectMgmt::Project` metadata and `AudioCore::Transport` tuning parameters.

## Key Components

- **ProjectSetupDialog** — Top-level modal dialog containing grouped controls (Start/Length, Frame Rate, Display Format & Offsets, Audio Engine defaults).  Supplies setters/getters for every field so controllers can load current project values and capture user edits.
- **ProjectSetupModel** — Lightweight POD struct describing the dialog state (start, length, frame rate, display format, offsets, sample rate, bit depth, file type, pan law).  Used to pass configuration in and out of the dialog without tight coupling to engine classes.
- **ProjectSetupValidator** — Helper that ensures values are consistent (e.g., start <= length, offsets within valid ranges).  Currently stubbed but centralises future validation logic.

## Responsibilities
- Mirror control layout: grouped `LabelBox`-style sections, timecode editors with inverse color theme, drop-downs for frame rate/display format/file type/pan law, and standard Help/OK/Cancel buttons.
- Provide RAII-friendly accessors so code can call `SetModel/GetModel` and integrate with undo/redo or immediate application patterns.
- Surface callbacks (`WhenHelp`, `WhenApply`) to coordinate with help system and commit actions.

## Future Enhancements (see PLAN.md)
- Replace placeholder validation with full range checking and warnings.
- Hook into `ProjectMgmt::History` to push undo entries when project settings change.
- Add binding to `TransportUI` so display format updates propagate to rulers and info lines instantly.
- Support preset storage for frequently used project templates.
