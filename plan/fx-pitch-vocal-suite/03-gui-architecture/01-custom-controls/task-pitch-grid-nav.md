# Task: Pitch Graph Grid and Navigation

This task involves improving the `PitchGraphEditor` by adding a proper musical pitch grid and synchronized time-based navigation.

## Objective

To replace the simple dummy grid with a semi-tonal musical grid (piano roll style) and implement zooming/scrolling.

## Key Actions

1.  **Implement Pitch-to-Y Mapping:**
    -   Define a range of MIDI notes (e.g., C1 to C6).
    -   Draw horizontal lines for each semi-tone, with darker lines for "natural" notes (white keys) and lighter/different colors for accidentals (black keys).
    -   Add pitch labels (e.g., "C3", "G#3") on the left side.
2.  **Implement Time-to-X Mapping:**
    -   Support a horizontal zoom level (pixels per second or pixels per beat).
    -   Implement horizontal scrolling.
3.  **Synchronization:**
    -   Ensure `PitchGraphEditor` and `WaveformStrip` use the same time-to-X mapping and scroll position.
4.  **Interactive Zoom/Scroll:**
    -   Use `MouseWheel` for vertical zoom (pitch) or horizontal zoom (time) with modifiers.
    -   Implement middle-mouse drag or scrollbar for navigation.

## Acceptance Criteria

1.  A musical pitch grid is visible in the `PitchGraphEditor`.
2.  Detected pitch points are correctly mapped to their musical pitch on the Y-axis.
3.  The view can be scrolled horizontally, and the `WaveformStrip` stays in sync.

## Risks

- **Coordinate Complexity:** Managing multiple zoom levels and scroll offsets across two different controls can lead to synchronization bugs. (Mitigation: Use a shared `ViewModel` or parent-level state).
