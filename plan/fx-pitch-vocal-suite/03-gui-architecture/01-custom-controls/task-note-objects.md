# Task: Note Objects and Manual Correction

This task involves adding the ability to create, move, and resize "note" blocks in the `PitchGraphEditor` to set target pitches for correction.

## Objective

To implement the "piano roll" style editing interface for manual pitch correction.

## Key Actions

1.  **Define `PitchNote` Structure:**
    -   `startTime`, `duration`, `midiNote`.
    -   Store in `PitchVocalProcessor` (or a separate `PitchModel`).
2.  **Rendering:**
    -   Draw rectangular blocks for each note in the `PitchGraphEditor`.
    -   Render notes with rounded corners and semi-transparent fills.
    -   Show note name labels on the blocks.
3.  **Interaction:**
    -   `LeftDoubleDown`: Create a new note at mouse position.
    -   `LeftDown`: Select a note.
    -   `LeftDrag`: Move note (pitch or time) or resize (duration).
    -   `KeyDown` (Delete): Remove selected note.
4.  **Processor Integration:**
    -   Ensure the list of notes is available to the audio thread for future correction logic.

## Acceptance Criteria

1.  Notes can be created by double-clicking in the grid.
2.  Notes can be moved and resized with the mouse.
3.  Notes are correctly mapped to the musical pitch and time grid.
4.  Selection state is visible.

## Risks

- **Collision Logic:** Handling overlapping notes or ensuring reasonable placement.
- **Undo/Redo:** Manual editing typically requires undo support. (Mitigation: Implement a simple state stack later).
