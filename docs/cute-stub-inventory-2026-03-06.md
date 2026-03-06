# Cute Stub Inventory (2026-03-06)

## Purpose
Inventory temporary compile-safe stubs introduced during phase-2 bring-up and define next action per file.

## Confirmed compile-safe stubs introduced in bring-up
- `src/AudioCore/CuteClip.cpp`
  - Current state: header include only (no symbols emitted).
  - Reason: avoid conflicting duplicate `CuteClip` implementation with `CuteAudioClip` type hierarchy.
  - Next action: decide whether to remove from `.upp` via guard or port/rename legacy clip implementation.

- `src/AudioCore/CuteMixer.cpp`
  - Current state: header include + stub comment.
  - Reason: legacy UI implementation referenced undeclared/obsolete types and conflicted with active mixer model.
  - Next action: port to current UI/type graph or guard from build until integration is planned.

- `src/AudioFX/Calibration.cpp`
  - Current state: header include + delegation comment.
  - Reason: duplicate `Calibration::*` symbol definitions with `src/Devices/Calibration.cpp`.
  - Next action: keep single source of truth in Devices or split namespaces/types explicitly.

- `src/AudioFX/SpatialDSP.cpp`
  - Current state: header include + stub comment.
  - Reason: duplicate/redefining DSP classes already implemented in `DSP.*`.
  - Next action: either merge unique logic into `DSP.*` or exclude this legacy unit.

- `src/AudioFX/SpatialDSPAdditional.cpp`
  - Current state: header include + stub comment.
  - Reason: companion legacy unit for SpatialDSP with overlapping symbols.
  - Next action: merge unique logic into active DSP modules or exclude.

## Non-blocking placeholder implementations (pre-existing)
- `src/AudioCore/Mixer.cpp`
- `src/AudioCore/MidiPreview.cpp`
- `src/AudioFX/SignalBus.cpp`
- `src/AudioFX/ModMatrix.cpp`
- `src/AudioFX/EQ.h`
- `src/AudioFX/Crossover.h`
- `src/AudioFX/Splitter.h`

These compile and are not build blockers; they remain behavior-parity debt.

## Current decision boundary
- Build stability is currently prioritized.
- Any replacement of confirmed stubs must preserve `script/build.py -j2 Cute` green status.
