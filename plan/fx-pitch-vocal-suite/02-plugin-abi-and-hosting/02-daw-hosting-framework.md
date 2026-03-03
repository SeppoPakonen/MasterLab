# GUI Architecture: Plugin Hosting in MasterLab DAW

This document defines how `PluginEditor` components are hosted within the MasterLab DAW environment.

## `PluginHost` Component

- **Location:** `src/AudioUI/`
- **Base Class:** `Upp::ParentCtrl`
- **Purpose:** To provide a standardized "frame" for plugin editors when they are loaded inside the DAW's rack or mixer.

## Responsibilities

1.  **Editor Embedding:** Hosts a `PluginEditor` instance.
2.  **Parameter Synchronization:**
    - Bridges the `PluginProcessor` parameters to the `PluginEditor`.
    - Handles automation updates from the DAW's timeline.
3.  **Standardized Header/Footer:**
    - Displays plugin name, bypass toggle, preset selector, and generic "cog" menu for settings.
4.  **Resizing:** Manages how the plugin editor is scaled or scrolled within the DAW's UI.

## Integration with `RackView`

`RackView` will be updated to support adding `PluginHost` instances:

```cpp
void RackView::AddPlugin(PluginProcessor& processor, PluginEditor& editor) {
    PluginHost* host = new PluginHost();
    host->SetPlugin(processor, editor);
    AddModule(*host, processor.GetName());
}
```

## Benefits

- **Decoupling:** `PluginEditor` doesn't need to know it's being hosted by the MasterLab DAW specifically.
- **Unified Look:** All plugins in the DAW get the same management controls (bypass, presets).
- **Automation Support:** Centralized logic for mapping DAW automation curves to plugin parameters.

## Next Steps

1.  Implement `PluginHost` in `src/AudioUI/PluginHost.h` and `src/AudioUI/PluginHost.cpp`.
2.  Update `RackView` to provide better support for these hosted plugins.
3.  Refactor `PitchVocalSuite` to be loadable via this `PluginHost`.
