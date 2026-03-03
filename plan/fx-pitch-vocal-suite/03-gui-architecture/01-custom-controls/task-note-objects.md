# Task: Note Objects and Manual Correction

This task involves adding the ability to create, move, and resize "note" blocks in the `PitchGraphEditor` to set target pitches for correction.

## Objective

To implement the "piano roll" style editing interface for manual pitch correction.

## Key Actions

1.  **Define `PitchNote` Structure:** [DONE]
    -   `startTime`, `duration`, `midiNote`.
    -   Store in `PitchVocalProcessor` (or a separate `PitchModel`).
2.  **Rendering:** [DONE]
    -   Draw rectangular blocks for each note in the `PitchGraphEditor`.
    -   Render notes with rounded corners and semi-transparent fills.
    -   Show note name labels on the blocks.
3.  **Interaction:** [DONE]
    -   `LeftDoubleDown`: Create a new note at mouse position. [DONE - LeftDouble]
    -   `LeftDown`: Select a note. [DONE]
    -   `LeftDrag`: Move note (pitch or time) or resize (duration). [DONE - MouseMove with K_MOUSELEFT]
    -   `KeyDown` (Delete): Remove selected note. [TODO - Keyboard support]
4.  **Processor Integration:** [DONE]
    -   Ensure the list of notes is available to the audio thread for future correction logic.

## Acceptance Criteria

1.  Notes can be created by double-clicking in the grid. [DONE]
2.  Notes can be moved and resized with the mouse. [DONE]
3.  Notes are correctly mapped to the musical pitch and time grid. [DONE]
4.  Selection state is visible. [DONE]

## Risks

- **Collision Logic:** Handling overlapping notes or ensuring reasonable placement.
- **Undo/Redo:** Manual editing typically requires undo support. (Mitigation: Implement a simple state stack later).
