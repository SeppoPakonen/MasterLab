# Reuse Candidates for `PitchVocalSuite`

This document lists candidate packages and components for reuse in the `PitchVocalSuite` development.

## Internal Packages (`./src/`)

- **`AudioAnalysis`:** Essential for pitch detection algorithms (FFT, autocorrelation, etc.).
- **`DSP`:** Foundational signal processing tools.
- **`AudioCore`:** Basic audio types and processing structures.
- **`AudioUI`:** Reusable UI components for audio plugins (meters, dials, etc.).
- **`PluginSDK`:** The interface for various plugin formats.
- **`Math`:** General mathematical utilities.
- **`CtrlLog`:** Logging within the U++ framework.
- **`Theme`:** Consistent look and feel using U++ native skins.

## External U++ Resources (`/common/active/sblo/Dev/ai-upp/`)

- **`AudioCtrl`:** Custom U++ controls for audio applications.
- **`SoftAudio`:** High-level audio abstractions and processing.
- **`CaptureScreenDll`:** Example reference for building dynamic link libraries (DLLs/SOs) with U++.

## Strategy for Reuse

1.  **Prefer Internal:** Use existing `MasterLab` packages first to maintain tight integration.
2.  **Evaluate External:** Inspect `AudioCtrl` and `SoftAudio` for specialized components (e.g., specific pitch display widgets) that might save time.
3.  **Porting:** If a component is highly generic and useful beyond `MasterLab`, consider moving it to the external `ai-upp` repository.
