# Task: Parameter Model Integration

This task involves connecting the `PitchVocalSuite` UI to the `PluginProcessor` parameters.

## Objective

To establish a two-way synchronization between the U++ UI controls (`PitchVocalTopBar`) and the underlying DSP parameter state in `PitchVocalProcessor`.

## Key Actions

1.  **Define Parameters:** [DONE]
    -   Define core parameters in `PitchVocalProcessor` using `PluginSDK::ParameterSet`.
    -   Example: `speed` (0.0 to 1.0), `vibrato` (0.0 to 1.0), `algorithm` (int 0, 1, 2).
2.  **UI Synchronization:** [DONE]
    -   Implement `SyncToProcessor()` in `PitchVocalEditor` to update the DSP state when UI controls change.
    -   Implement `SyncFromProcessor()` in `PitchVocalEditor` to update the UI controls when the host changes a parameter (e.g., via automation or preset load).
3.  **Attach Events:** [DONE]
    -   Use U++ `WhenAction` callbacks on the `SliderCtrl` and `DropList` in `PitchVocalTopBar` to trigger the sync.

## Acceptance Criteria

1.  Moving the Speed or Vibrato sliders in the UI updates the `PluginProcessor` state. [DONE]
2.  Changing the Algorithm dropdown updates the `PluginProcessor` state. [DONE]
3.  The plugin builds and runs correctly. [DONE]

## Risks

- **Thread Safety:** Ensuring that UI updates to parameters don't cause data races with the real-time audio thread executing `Process()`. (Typically handled by the `ParameterSet` atomics or a messaging queue).
