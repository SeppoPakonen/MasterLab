# Custom Control: `PitchGraphEditor`

This document defines the architecture of the custom U++ control for pitch graph editing.

## Functionality

- **Visual Grid:** Semi-tonal grid representing musical pitches over time.
- **Pitch Curves:** Drawing of detected pitch (raw) and corrected pitch (target).
- **Note Objects:** Rectangular "notes" that can be moved or resized to set target pitch.
- **Interactive Editing:** Mouse-based manipulation of pitch points and notes.
- **Zoom/Scroll:** Synchronized with the `WaveformStrip`.

## Implementation details

- **Base Class:** `Ctrl`.
- **Drawing:** Override `Paint(Draw& w)` and use `w.DrawLine`, `w.DrawRect`, `w.DrawPolyline`, etc.
- **Coordinate System:**
    - X-axis: Time (samples or beats).
    - Y-axis: Pitch (MIDI cents or frequency).
- **Event Handling:** Override `LeftDown`, `LeftDrag`, `MouseMove`, `MouseWheel` for interaction and navigation.
- **Optimization:** Use backing Store (offscreen buffer) if the drawing becomes too complex for real-time updates.

## Performance Considerations

- For large datasets (e.g., several minutes of audio), implement level-of-detail (LOD) rendering for the pitch curves.
- Only redraw the visible portion of the graph.
