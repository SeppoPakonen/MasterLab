# Risks and Mitigations: `PitchVocalSuite`

This document outlines potential technical and project-related risks for the `PitchVocalSuite` project.

## High Risks

- **Plugin GUI Hosting (U++ Embedding):** Embedding a U++ GUI within a plugin host (LV2/VST) is architecturally complex.
    - **Mitigation:** Research three strategies (Native Child Window, VIRTUALGUI, new `CtrlCore` backend) and prototype small experiments early.
- **Pitch Detection Accuracy:** Creating low-latency, high-accuracy pitch detection for monophonic signals (vocals) is a significant DSP challenge.
    - **Mitigation:** Reuse existing `AudioAnalysis` components and refine the algorithm in phases.
- **Linux Plugin Ecosystem (LV2):** Developing a stable and portable LV2 plugin on Linux involves complex build and deployment challenges.
    - **Mitigation:** Use Gentoo Linux as the primary validation platform and refer to existing plugin SDKs and best practices.

## Medium Risks

- **U++ Framework Limitations:** The U++ framework might not natively support all features required for a high-performance audio plugin GUI.
    - **Mitigation:** Create custom `Ctrl` components for specialized UI elements (e.g., the pitch graph editor) and potentially explore VIRTUALGUI.
- **Build System Integration:** The current `script/build.py` doesn't find packages outside of `src/`.
    - **Mitigation:** Update the build script to support multiple package roots (e.g., `effects/`, `instruments/`).

## Low Risks

- **Bitmap Skinning:** The choice to use native-like controls may result in a "less modern" look.
    - **Mitigation:** Use custom drawing code (e.g., `Draw::DrawLine`, `Draw::DrawText`) for a polished and performant UI.
- **Dependency Sprawl:** Excessive dependencies could make the plugin harder to build and distribute.
    - **Mitigation:** Be selective with `uses` in `PitchVocalSuite.upp` and favor internal `MasterLab` packages.
