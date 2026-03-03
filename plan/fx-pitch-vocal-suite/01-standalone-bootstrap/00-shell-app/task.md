# Task: Standalone Shell Application (`PitchVocalSuite`)

This task involves creating a minimal standalone U++ application shell for the `PitchVocalSuite` project.

## Purpose

To establish a runnable application that demonstrates:
- Correct package wiring and dependency resolution.
- A functional U++ GUI shell (main window/editor).
- Ability to host placeholder panels for future pitch graph and timeline.

## Implementation Details

- **Target:** Standalone executable.
- **Main Window:** A basic `TopWindow`-derived class.
- **UI Structure:**
    - Top area: Placeholder global controls.
    - Center area: Placeholder pitch graph area.
    - Bottom area: Placeholder waveform/timeline strip.
- **Build Method:** `script/build.py PitchVocalSuite`. (Note: Build script must be updated first).

## Acceptance Criteria

1.  The application builds successfully using `script/build.py`.
2.  The application launches and displays a main window.
3.  The main window contains the defined placeholder sections.
4.  No errors or warnings during the build or launch.

## Dependencies

-   U++ Framework (`CtrlLib`).
-   `PluginSDK`, `AudioCore`, `DSP`, `AudioUI`.
-   Updated `script/build.py` to support `effects/` packages.
