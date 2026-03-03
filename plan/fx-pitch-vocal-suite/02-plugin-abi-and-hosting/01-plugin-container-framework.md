# GUI Architecture: Plugin Container Framework

This document defines the architecture for a generic plugin container framework that allows U++ GUIs to be hosted in various environments (Standalone, LV2, VST, MasterLab).

## Core Concepts

### 1. `PluginEditor` (Base Class)
- **Location:** `src/PluginSDK/`
- **Base Class:** `Upp::Ctrl`
- **Purpose:** A generic container for plugin UIs. It decouples the UI from the windowing system.
- **Key Methods:**
    - `virtual void SetProcessor(PluginProcessor* p)`: Connects the UI to its DSP counterpart.
    - `virtual void SyncToProcessor()`: Updates the UI based on processor state.
    - `virtual void SyncFromProcessor()`: Updates the processor based on UI interaction.

### 2. `PluginWindow` (Hosting Wrapper)
- **Location:** `src/PluginSDK/` or `src/Windowing/`
- **Base Class:** `Upp::TopWindow` (for Standalone) or platform-specific wrapper.
- **Purpose:** Wraps a `PluginEditor` for a specific hosting environment.
- **Responsibilities:**
    - Managing the main window lifecycle.
    - Handling menu bars, status bars (if needed for standalone).
    - Providing the parent window handle for plugin-style embedding.

### 3. Unified Hosting API
- A set of functions or a factory to create the appropriate hosting wrapper.
- Example: `PluginWindow* CreateStandaloneWindow(PluginEditor* editor);`

## Implementation Strategy

1.  **Define `PluginEditor` in `src/PluginSDK`:** Ensure it's a lightweight `Ctrl` that can be embedded anywhere.
2.  **Refactor `PitchVocalSuite`:**
    - Change `PitchVocalEditor` to inherit from `PluginEditor` instead of `TopWindow`.
    - Move all UI logic into `PitchVocalEditor`.
3.  **Create a Standalone Bootstrap Wrapper:**
    - In `effects/PitchVocalSuite/main.cpp` (or within `PitchVocalSuite.cpp`), create a `TopWindow` that hosts the `PitchVocalEditor`.

## Benefits
- **Reusability:** The same `PitchVocalEditor` can be used in the standalone app and the LV2 plugin.
- **Consistency:** All MasterLab plugins follow the same UI/Processor separation.
- **Portability:** Simplifies embedding in non-U++ hosts.
