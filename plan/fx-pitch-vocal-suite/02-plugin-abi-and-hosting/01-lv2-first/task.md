# Task: LV2 ABI Integration (Phase 1)

This task involves creating the first LV2 ABI wrapper for the MasterLab plugin framework.

## Objective

To create a shared library (.so) that follows the LV2 specification and can host a `PluginProcessor` and `PluginEditor`.

## Key Actions

1.  **Create `src/PluginABI/LV2` Package:** [STARTED]
    -   Define the LV2 entry points (`lv2_instantiate`, `lv2_run`, etc.). [SKELETON IN PLACE]
    -   Implement the `LV2UI` interface to host a U++ GUI. [SKELETON IN PLACE]
2.  **Define the Translation Layer:** [STARTED]
    -   Map LV2 port buffers to `PluginSDK::ProcessContext`. [IN PROGRESS]
    -   Map LV2 control ports to `PluginSDK::ParameterSet`. [TODO]
3.  **Experimental X11 Embedding:**
    -   Implement the X11-based `LV2UI` that uses the native child window strategy to embed `PluginEditor`.
4.  **Metadata Generation:**
    -   Create a script or U++ utility to generate the required `.ttl` files for LV2 (manifest.ttl, plugin.ttl).

## Acceptance Criteria

1.  A shared library is produced that is recognized by LV2 hosts (e.g., Jalv, Carla, Ardour).
2.  The plugin can be instantiated by a host.
3.  The GUI (initially a simple `PluginEditor`) is successfully embedded in the host's window.
4.  Audio passes through the plugin (even if just bypassed).

## Risks

- **LV2 C++ Wrappers:** Deciding whether to use a library like `distrho-plugin-framework` or write the ABI wrapper from scratch using raw LV2 headers.
- **X11 Event Loop:** Synchronizing the U++ event loop with the host's X11 event processing can be tricky.
- **Symbol Visibility:** Ensuring the correct symbols are exported in the shared library.
