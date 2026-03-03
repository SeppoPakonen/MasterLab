# Overview: Repository Survey

This document summarizes the current state of the repository as it pertains to the `PitchVocalSuite` development.

## Current Files

The following files exist under `effects/PitchVocalSuite/`:
- `AGENTS.md`
- `PitchVocalSuite.cpp`
- `PitchVocalSuite.h`
- `PitchVocalSuite.upp`

## `.upp` Configuration

The existing `PitchVocalSuite.upp` uses:
- `CtrlLib`
- `PluginSDK`
- `AudioCore`
- `DSP`
- `AudioUI`

It contains three files:
- `AGENTS.md`
- `PitchVocalSuite.h`
- `PitchVocalSuite.cpp`

## Build System Observations

- The `script/build.py` is currently configured with `src_root = repo_root / "src"`.
- It will not find `PitchVocalSuite` in `effects/` if only the name is provided, unless the script is updated to search other directories (e.g., `effects/`, `instruments/`).
- Alternatively, `PitchVocalSuite` could be moved to `src/` to follow existing patterns.
- `umk` is the expected build tool for U++ packages.

## Reusable Components

Many packages exist under `./src/` that could be useful:
- `AudioCore` (already used)
- `DSP` (already used)
- `AudioUI` (already used)
- `AudioAnalysis` (likely needed for pitch detection)
- `PluginSDK` (already used)

## Existing External U++ Resources

- `/common/active/sblo/Dev/ai-upp/` contains `AudioCtrl` and `SoftAudio` packages, which should be explored for reuse.
