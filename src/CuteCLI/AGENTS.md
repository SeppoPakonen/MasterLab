# CuteCLI Package

## Purpose
`CuteCLI` is a headless command-line harness for smoke-testing core Cute functionality without `GUI`.

## Scope
- Create a basic project artifact on disk.
- Simulate MIDI note activity through `am::Synth::VoiceManager`.
- Render a simple WAV file for offline verification.

## Constraints
- `CuteCLI.upp` main configuration must not enable `GUI`.
- Keep dependencies focused on non-GUI packages.
