# Cute Parity Audit (2026-03-06)

## Build Graph
- Command: `script/build.py -j2 Cute`
- Result: links successfully
- Compiled package count: 40

## Reachable Package .upp Omissions
- Method: for each compiled local package under `src/*`, list `*.h/*.cpp/*.icpp/*.iml/AGENTS.md` files not referenced in package `.upp`.
- Missing manifest entries: 61

### Missing Counts By Package
- AudioCore: 21
- AudioFX: 23
- Devices: 2
- Editors: 1
- FileIO: 6
- MIDI: 1
- Preferences: 1
- ProjectMgmt: 1
- Scores: 1
- Tooling: 1
- TransportPrefs: 1
- Video: 1
- Windowing: 1

### Missing Entries
- AudioCore: src/AudioCore/CuteAudioFile.h
- AudioCore: src/AudioCore/CuteCurveFile.h
- AudioCore: src/AudioCore/CuteEngine.h
- AudioCore: src/AudioCore/CuteMixer.cpp
- AudioCore: src/AudioCore/CuteMixer.h
- AudioCore: src/AudioCore/CuteMonitor.h
- AudioCore: src/AudioCore/Mixer.cpp
- AudioCore: src/AudioCore/Mixer.h
- AudioCore: src/AudioCore/CuteAudioBuffer.h
- AudioCore: src/AudioCore/CuteAudioClip.h
- AudioCore: src/AudioCore/CuteAudioEngine.h
- AudioCore: src/AudioCore/CuteAudioMadFile.h
- AudioCore: src/AudioCore/CuteAudioMeter.h
- AudioCore: src/AudioCore/CuteAudioMonitor.h
- AudioCore: src/AudioCore/CuteAudioPeak.h
- AudioCore: src/AudioCore/CuteAudioSndFile.h
- AudioCore: src/AudioCore/CuteAudioVorbisFile.h
- AudioCore: src/AudioCore/CuteClip.cpp
- AudioCore: src/AudioCore/CuteClip.h
- AudioCore: src/AudioCore/CuteCurve.h
- AudioCore: src/AudioCore/CuteCurveFile.cpp
- AudioFX: src/AudioFX/GainNormalization.h
- AudioFX: src/AudioFX/Limiter.cpp
- AudioFX: src/AudioFX/Limiter.h
- AudioFX: src/AudioFX/SpatialDSP.cpp
- AudioFX: src/AudioFX/SpatialDSP.h
- AudioFX: src/AudioFX/SpatialDSPAdditional.cpp
- AudioFX: src/AudioFX/Splitter.cpp
- AudioFX: src/AudioFX/Splitter.h
- AudioFX: src/AudioFX/ZenCoreCatalogue.cpp
- AudioFX: src/AudioFX/ZenCoreCatalogue.h
- AudioFX: src/AudioFX/AGENTS.md
- AudioFX: src/AudioFX/Calibration.cpp
- AudioFX: src/AudioFX/Compressor.cpp
- AudioFX: src/AudioFX/Compressor.h
- AudioFX: src/AudioFX/Crossover.cpp
- AudioFX: src/AudioFX/Crossover.h
- AudioFX: src/AudioFX/Effect.h
- AudioFX: src/AudioFX/EffectChain.h
- AudioFX: src/AudioFX/EQ.cpp
- AudioFX: src/AudioFX/EQ.h
- AudioFX: src/AudioFX/Gain.cpp
- AudioFX: src/AudioFX/Gain.h
- AudioFX: src/AudioFX/GainNormalization.cpp
- Devices: src/Devices/Calibration.cpp
- Devices: src/Devices/Calibration.h
- Editors: src/Editors/AGENTS.md
- FileIO: src/FileIO/Backup.cpp
- FileIO: src/FileIO/Backup.h
- FileIO: src/FileIO/CuteClip.cpp
- FileIO: src/FileIO/CuteCurveFile.cpp
- FileIO: src/FileIO/Templates.cpp
- FileIO: src/FileIO/Templates.h
- MIDI: src/MIDI/AGENTS.md
- Preferences: src/Preferences/AGENTS.md
- ProjectMgmt: src/ProjectMgmt/AGENTS.md
- Scores: src/Scores/AGENTS.md
- Tooling: src/Tooling/AGENTS.md
- TransportPrefs: src/TransportPrefs/AGENTS.md
- Video: src/Video/AGENTS.md
- Windowing: src/Windowing/AGENTS.md

## Conversion Mapping Spot-check (tmp/q/src top-level .h/.cpp)
- Source files: 266
- After naive `qtractor* -> Cute*` rename, unresolved basenames: 2
  - `CuteAtomic`
  - `Cute_plugin_scan`
- Note: plugin scan functionality exists as `src/VSTHost/CutePluginScan.{h,cpp}`.

## Conclusion
- 1:1 parity is not complete yet because non-trivial parts of compiled local packages are not listed in `.upp` manifests.

## Update (same day)
- Added missing entries to `.upp` manifests for all local packages on the `Cute` build graph.
- Re-checked omissions on compiled local packages: `0` missing file entries.
- Rebuilt with `script/build.py -j2 Cute`: build and link now succeed.
- Note: several newly-enabled legacy units are currently compile-safe stubs to avoid duplicate symbol conflicts while preserving manifest inclusion.
