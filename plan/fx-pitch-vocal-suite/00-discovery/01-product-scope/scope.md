# Product Scope: `PitchVocalSuite`

This document defines the scope of the `PitchVocalSuite` project.

## Project Vision

Create a professional-grade pitch correction and vocal processing suite for Linux, built with the U++ framework, that can compete with existing industry standards in terms of sound quality and user experience.

## Target Audience

-   Musicians and audio engineers on Linux.
-   Producers using DAW environments that support LV2.
-   Users who prefer native-like UI over bitmap skinning.

## Key Features

-   **Pitch Correction:** High-quality pitch detection and correction algorithms.
-   **Graph Editor:** Timeline-based pitch editing (similar to Auto-Tune or Melodyne).
-   **Vocal Processing:** Vibrato control, note tools, and potentially other vocal-specific effects.
-   **Multi-Format:** Standalone, LV2, and future support for VST, CLAP, and LADSPA.

## Primary Targets

-   **Gentoo Linux:** Development and primary validation platform.
-   **LV2:** The first priority plugin target on Linux.

## Out of Scope (Initially)

-   Full autotune correction DSP (will start with a skeleton).
-   Polished plugin ABI support for every format (VST3/CLAP/LADSPA follow later).
-   Skin-perfect replication of competitors.
-   Broad refactoring of the entire `MasterLab` repo.
