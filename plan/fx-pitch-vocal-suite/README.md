# Track: `fx-pitch-vocal-suite`

This track covers the development of a comprehensive pitch-correction and vocal-processing suite in the MasterLab repository, utilizing the Ultimate++ (U++) framework.

## Overview

The goal is to create a feature-rich vocal processing plugin family, initially targeting standalone and LV2 on Linux, with later support for VST, CLAP, and LADSPA. The suite will feature a graph-editor-based GUI for pitch correction, similar to industry standards like Auto-Tune, but built with U++ native and custom controls.

## Phases

### 00-discovery
- Repository survey, reuse candidates, and build system observations.
- Product scope definition and risk analysis.

### 01-standalone-bootstrap
- Establishing a minimal runnable standalone application shell.
- Package wiring and dependency management.

### 02-plugin-abi-and-hosting
- Research and comparison of GUI-hosting strategies within plugin windows.
- Initial LV2 ABI integration experiments.

### 03-gui-architecture
- Defining the U++ layout and custom control architecture.
- Prototyping the pitch graph editor and waveform strip.

### 04-pitch-engine-skeleton
- Implementation of the core DSP analysis and correction pipeline.
- Parameter model and automation support.

### 05-lv2-bringup
- Full LV2 plugin implementation based on the validated architecture.

### 06-future-plugin-targets
- Expanding support to other plugin formats (VST3, CLAP, LADSPA).

## Technical Direction

- **Framework:** Ultimate++ (U++).
- **GUI:** `CtrlLib`-style native-like controls; no bitmap skinning.
- **Platform:** Primary development on Gentoo Linux.
- **Milestones:** Standalone-first, then LV2, then others.
