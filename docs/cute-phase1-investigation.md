# Cute Phase 1 Investigation

## Survey
- Qtractor source root contains `294` direct files in `tmp/q/src/` that are reasonable phase-1 conversion targets.
- Nested directories under `tmp/q/src/` include vendored SDKs (`vst3`, `clap`), assets (`images`), and translations; these are intentionally excluded from the one-file conversion backlog because they are not qtractor application translation units.
- `src/daw/` is currently only an assembly stub (`daw.upp`, `daw.h`, `main.cpp`). The real MasterLab architecture lives in the package directories under `src/*`.
- Existing packages already mirror a Cubase-style decomposition (`AudioCore`, `ProjectWindow`, `Editors`, `VSTHost`, `VSTConnections`, `Preferences`, `ProjectMgmt`, and others). That makes package-directed conversion practical in phase 1.

## Working Interpretation
- `src/Cute` should be treated as the new assembly root for the converted application, analogous to `src/daw`.
- Converted qtractor classes should land in existing `src/*` package directories whenever there is an obvious home, so stub packages become populated instead of duplicated.
- Phase 1 should avoid build validation entirely; success is measured by source coverage and structural fidelity, not by compilation.
- Naming policy for converted outputs: classes and functions use `CapitalCase`, while variables use `lower_underscore`; camelCase should not appear in new code.

## Package Mapping Heuristics
- `AudioCore`: 38 files. Session, engine, clip, curve, mixer, and low-level audio runtime structures.
- `AudioEditing`: 20 files. Edit operations, range/tempo dialogs, and offline audio-edit helpers.
- `AudioMaster`: 16 files. Main application shell, message surfaces, and top-level window hosting.
- `Browser`: 2 files. Media/file browser list controls.
- `Cute`: 3 files. Assembly entrypoint or phase-level integration artifact for the new Cute application root.
- `Devices`: 6 files. Device backends, external session adapters, and runtime connectivity helpers.
- `ExportAudioMixdown`: 3 files. Audio export dialog and mixdown-related workflow UI.
- `FileIO`: 12 files. Project document, file browsing, import/export, and archive persistence.
- `MIDI`: 76 files. MIDI engine, MIDI data model, control surfaces, and instrument definitions.
- `Preferences`: 11 files. Global options, palettes, and shortcut/preferences dialogs.
- `ProjectMgmt`: 17 files. Undoable command surfaces and command-routing definitions.
- `ProjectWindow`: 22 files. Track-area/project-area widgets and supporting project window controls.
- `Theme`: 2 files. Reusable visual widgets with application-wide look/feel implications.
- `Tooling`: 7 files. Low-level utility helpers and observer/container primitives.
- `TransportUI`: 9 files. Transport and timeline widgets such as scales, spinboxes, and meters.
- `VSTConnections`: 13 files. Audio/MIDI connection dialogs and bus-routing UI.
- `VSTHost`: 37 files. Plugin discovery, wrappers, scan surfaces, and plugin-facing UI.

## Risks
- Some files sit across package boundaries in qtractor (for example, `qtractorMainForm`, session/track widgets, and plugin UI forms). The per-file tasks therefore record a suggested package, not an immutable rule.
- Qt `.ui` forms do not map 1:1 to U++ `.lay` usage in every case. Manual judgement is still required during conversion.
- `src/Cute` does not exist yet. Phase 2 needs to create the assembly files and finalize the `uses(...)` closure after enough phase-1 files exist.

## Recommended Phase 2 Entry Point
- Start with Cute assembly creation plus package manifest updates, then run the first compile and triage errors by package boundary instead of by original qtractor subsystem.
