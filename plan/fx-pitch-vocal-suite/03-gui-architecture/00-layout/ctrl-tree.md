# GUI Architecture: U++ Control Tree

This document defines the U++ control hierarchy for the `PitchVocalSuite` GUI.

## UI Layout Structure

The main window (`PitchVocalEditor`) will use a vertical layout:

1.  **`PitchVocalTopBar` (`StaticRect` or `ParentCtrl`):**
    -   Global controls: Algorithm selection, correction speed, vibrato amount.
    -   Meters: Input/Output level.
2.  **`PitchGraphEditor` (Custom `Ctrl`):**
    -   Central area for pitch display and manual correction.
    -   Handles custom drawing for the pitch grid, notes, and correction curves.
3.  **`WaveformStrip` (Custom `Ctrl`):**
    -   Lower strip for waveform visualization and timeline navigation.
    -   Synchronized scrolling with `PitchGraphEditor`.

## Component Summary

| Component | U++ Base | Responsibility |
| :--- | :--- | :--- |
| `PitchVocalEditor` | `TopWindow` / `Ctrl` | Main container and event dispatcher. |
| `PitchVocalTopBar` | `ParentCtrl` | Global settings and meters. |
| `PitchGraphEditor` | Custom `Ctrl` | Interactive pitch correction grid. |
| `WaveformStrip` | Custom `Ctrl` | Waveform display and timeline sync. |
| `CorrectionToolbox` | `StaticRect` | Buttons for different correction modes/tools. |

## Event Handling

-   Custom `Ctrl` components will override `Paint()`, `LeftDown()`, `MouseMove()`, etc.
-   Data synchronization between components will be handled via callbacks or shared models.
-   The editor will interact with the underlying DSP engine through a thread-safe parameter model.
