# qtractor `src/CMakeLists.txt` Conversion Notes

## Source
- Original file: `tmp/q/src/CMakeLists.txt`
- Phase: Cute phase 1
- Intent: translate the legacy Qt/CMake source inventory into U++ assembly planning without building yet.

## What The Original File Does
- Declares one main executable for the legacy application.
- Declares one helper executable for plug-in scanning.
- Generates `config.h` from `config.h.cmake`.
- Enables Qt autogen for `.ui`, meta-object, and resource compilation.
- Enumerates the full direct source inventory for headers, `.cpp` files, `.ui` forms, translations, and `qtractor.qrc`.
- Pulls in optional platform and plugin SDK details for JACK, ALSA, sndfile, vorbis, rubberband, aubio, LV2, VST2, VST3, CLAP, XCB, and related dependencies.
- Defines install payloads for translations, icons, desktop metadata, mimetypes, manpages, metronome audio files, instrument definitions, and palette presets.

## U++ Interpretation
- `Cute` should eventually replace the legacy CMake target as the top-level assembly invoked by `script/build.py Cute`.
- The direct file inventory should not become one giant package. Instead, files should be routed into existing MasterLab packages:
  - application shell -> `src/AudioMaster`
  - audio/session engine -> `src/AudioCore`
  - MIDI/editor/model code -> `src/MIDI`
  - plugin wrappers/scanner -> `src/VSTHost`
  - routing dialogs -> `src/VSTConnections`
  - file/document/archive support -> `src/FileIO`
  - command surfaces -> `src/ProjectMgmt`
  - options/preferences -> `src/Preferences`
  - track/project area widgets -> `src/ProjectWindow`
  - integration leftovers and assembly notes -> `src/Cute`
- Qt `.ui` coverage maps to U++ control/layout implementations; phase 1 only records that responsibility and converts those files separately.
- Qt resources and translation generation do not have a direct 1:1 U++ equivalent. They need explicit handling in phase 2 build tooling and packaging.

## Future Cute Assembly Shape
Expected phase-2 files:
- `src/Cute/Cute.upp`
- `src/Cute/Cute.h`
- `src/Cute/main.cpp`

Expected phase-2 responsibilities:
- define `uses(...)` for packages filled during phase 1
- wire startup and main window creation
- decide whether plugin scanning is a second executable, a tool mode, or a test/build helper
- make `script/build.py Cute` produce the executable later

## Main Executable Inventory
The original main target contains:
- 138 headers
- 128 `.cpp` files
- 25 `.ui` forms
- 1 Qt resource file
- optional VST3 SDK support sources

Those source files are now represented in `plan/cute/phase1/BACKLOG.md` as per-file conversion tasks.

## Helper Executable: Plug-in Scan Tool
The original build creates a second executable from:
- `qtractor_plugin_scan.cpp`
- optional VST3 SDK support sources

U++ options for phase 2:
- separate `CutePluginScan` assembly/package
- alternate `Cute` command-line mode
- helper target built by `script/build.py` beside the main app

No decision is required in phase 1; only the requirement is preserved.

## Config/Header Generation
The CMake file generates `config.h` from `config.h.cmake`.

U++ conversion direction:
- treat `config.h.cmake` as a feature inventory, not as a direct generated header
- phase 2 should convert the feature matrix into either
  - compile flags in the assembly/build script, or
  - a handwritten U++ configuration header under `src/Cute`

## Non-Source Payload Inventory
The original target installs:
- translations under `translations/`
- icons and desktop metadata under `images/`, `appdata/`, `mimetypes/`
- manpages under `man1/`
- metronome samples under `audio/`
- instrument definitions under `instruments/`
- palette presets under `palette/`

These should remain outside the initial code conversion flow and be handled by later packaging tasks.

## Manifest Notes For Later
When phase 2 starts:
- add `AGENTS.md` first in `src/Cute/Cute.upp`
- add the future `Cute.h` and `main.cpp`
- avoid listing converted files here if they already belong in existing packages
- keep `Cute` focused on assembly-level startup and integration
