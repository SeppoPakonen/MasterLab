# Custom Control: `WaveformStrip`

This document defines the architecture of the custom U++ control for waveform visualization and timeline navigation.

## Functionality

- **Waveform Rendering:** Displaying the audio waveform for monophonic vocal tracks.
- **Timeline/Ruler:** Visual indicators for time (seconds/beats).
- **Navigation:** Dragging to scroll, clicking to set playhead position.
- **Sync:** Tightly synchronized with the `PitchGraphEditor`.

## Implementation Details

- **Base Class:** `Ctrl`.
- **Drawing:** Override `Paint(Draw& w)` and use `w.DrawLine` or `w.DrawPolyline` for waveform peaks.
- **Waveform Data:** Use pre-calculated peaks for efficient rendering at different zoom levels.
- **Coordinate System:** Shared X-axis (Time) with the pitch editor.

## Features

- **Playhead:** Vertical line indicating current playback position.
- **Selection:** Ability to select a range for analysis or correction.
- **Tooltips:** Show time or note name at mouse position.

## Technical Details

- Use a `WaveformProvider` interface to decouple the UI from the audio storage format.
- Implement efficient caching for waveform peaks to allow smooth scrolling.
