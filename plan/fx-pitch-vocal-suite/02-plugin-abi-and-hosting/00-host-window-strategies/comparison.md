# GUI Hosting Comparison: U++ in Plugin Window

This document compares strategies for hosting a U++ GUI within a plugin's editor window (e.g., LV2/VST).

## Strategy A: Native Child Window Embedding

- **Concept:** Use the platform's native child window API (X11 on Linux, Win32 on Windows) to embed a U++ `TopWindow` as a child of the host-provided window handle.
- **Pros:**
    - High performance.
    - Matches U++ design for native window management.
- **Cons:**
    - Complexity in cross-platform window handle management.
    - Potential event handling issues (e.g., keyboard focus).

## Strategy B: VIRTUALGUI-like Approach

- **Concept:** Render the U++ GUI to an offscreen buffer (e.g., using OpenGL or a custom surface) and blit it to the host window. Redirect host input events to U++'s internal event loop.
- **Pros:**
    - High portability.
    - Simplified embedding (just need a drawing surface).
- **Cons:**
    - Higher overhead (rendering/blitting).
    - Complex event translation logic.

## Strategy C: New `CtrlCore` Backend

- **Concept:** Create a specialized U++ `CtrlCore` backend specifically for plugin hosting.
- **Pros:**
    - Cleanest long-term architecture.
    - Optimized for plugin constraints.
- **Cons:**
    - Significant engineering effort (modifying U++ core).
    - Might be overkill for initial bring-up.

## Recommendation

For the initial LV2 bring-up on Linux, **Strategy A (Native Child Window)** is the most direct path, as it leverages U++'s existing X11 support. **Strategy B (VIRTUALGUI)** should be kept as a backup if embedding issues arise.
