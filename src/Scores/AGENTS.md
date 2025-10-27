# Scores Package

## Overview
The Scores package handles music notation functionality including the notation model, layout engine, and notation functions. It provides the foundation for displaying and editing musical scores in traditional notation format.

## Key Components

### NotationModel
- Represents the musical content in score format
- Stores measures, notes, and musical attributes

### LayoutEngine
- Handles the visual layout of musical notation
- Manages page sizing, margins, and formatting

### Functions
- Provides notation-specific operations like transposition and quantization
- Handles score validation and processing

## Relations to Other Packages
- `CtrlLib`: UI controls and framework for score display
- `Draw`: Drawing functionality for notation rendering
- `Editors`: Integration with score editor components

## Package Classes Relations
- NotationModel provides data structure for scores
- LayoutEngine formats the notation for display
- Functions provide operations that work on the notation model

## Score Editor Support Roadmap

### Document & View State
- **`NotationDocument`** evolves into a façade over `MIDI::Part` data, exposing staff systems, voices, and articulations. Provides `CreateView(const ScoreViewState&)` returning immutable snapshots for UI rendering.
- **`ScoreViewState`** tracks zoom, visible staves, clef choices, note colors, and staff/timeline alignment. Syncs with `Preferences::PrefStore` for persistent defaults.
- **`SelectionSnapshot`** captures the active selection (notes, symbols, clefs) with metadata needed by `ScoreInfoBar`. Supplies helpers (`GetPrimaryNote()`, `AsRange()`, etc.).

### Symbol & Palette Catalogs
- **`SymbolCatalog`** enumerates all palettes used by the Symbols pane (Favorites, Clefs, Dynamics, Articulations, Lines, Misc).  Each entry describes glyph, group, tooltip, and insertion command.
- **`FavoritesRepository`** stores user-pinned symbols; integrates with `Preferences`.
- Export palette descriptors to JSON so UI can rebuild palettes without recompiling.

### Editing Services
- **`NotationCommandBuilder`** generates undoable operations (`InsertNote`, `ModifyPitch`, `GlueNotes`, `CreateChordSymbol`, etc.) consumed by `ProjectMgmt::CommandManager`.
- **`QuantizeState`** holds quantize/grid settings (grid type, length quantize, triplet/dotted flags) shared across Score/Key/List editors.
- **`StepInputEngine`** coordinates QWERTY/Step/MIDI input, hooking into `AudioCore::MidiPreview` for Acoustic Feedback.

### Layout & Hit Testing
- Extend `LayoutEngine` with hit-test queries (`HitTest(point)` returning `ScoreHitResult`) and measurement APIs for zoom scaling.
- Provide cached glyph metrics and ledger line calculations to keep `ScoreCanvas` lightweight.
- Integrate optional Guitar TAB rendering by mapping `NotationDocument` voices to linked tab staves (future work).

### Integration Points
- Works with `ProjectMgmt::SelectionService` to keep editor selections in sync with global context.
- Emits events to `AudioCore::Transport` for Auto-Scroll and playback follow.
- Shares quantize presets with `Editors::KeyEditor` for consistent behavior across MIDI editors.
