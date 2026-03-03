# LV2 Plugin Experiments: U++ GUI Hosting

This document outlines initial experiments for hosting a U++ GUI within an LV2 plugin on Linux.

## Objective

To validate the feasibility of embedding a U++ `TopWindow` (or equivalent) into a host-provided X11 window handle.

## Experiment 1: Native X11 Child Window

- **Goal:** Embed a U++ `TopWindow` into a parent X11 window.
- **Implementation:**
    - Use `TopWindow::Open(HWND parent)` (on Linux `HWND` is `Window` from Xlib).
    - Ensure U++ event loop integrates with the host's event processing.
- **Expected Result:** The U++ window appears inside the host's UI and responds to basic mouse events.

## Experiment 2: VIRTUALGUI with GLX

- **Goal:** Render U++ GUI to an OpenGL texture and display it in the host's X11 window.
- **Implementation:**
    - Use `VIRTUALGUI` backend.
    - Bridge host X11 events to `VIRTUALGUI` input methods.
- **Expected Result:** More portable rendering but potentially higher complexity in event routing.

## Experiment 3: Minimal LV2 Wrapper

- **Goal:** Create a skeleton LV2 plugin that opens a native X11 window and attempts to host a U++ `Ctrl`.
- **Implementation:**
    - Use a minimal LV2 C++ wrapper (e.g., `distrho-plugin-framework` or native LV2 headers).
    - Initialize U++ in the `ui:ui` portion of the LV2 plugin.

## Next Steps

1.  Create a small test C++ program that manually creates an X11 window and tries to host a U++ `TopWindow` as a child.
2.  Document any issues with keyboard focus or window resizing.
3.  Evaluate the need for a custom U++ `CtrlCore` backend if native embedding is too brittle.
