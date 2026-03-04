# qtractor `config.h.cmake` Conversion Notes

## Source
- Original file: `tmp/q/src/config.h.cmake`
- Phase: Cute phase 1
- Intent: preserve the legacy feature matrix for later U++ assembly/build integration.

## What The Original File Represents
The file is a generated-configuration template, not ordinary application code. It captures:
- project metadata strings
- install path defaults
- debug/optimization switches
- system header availability
- optional audio/MIDI/plugin backend support
- optional UI/platform integration flags

## U++ Direction
Phase 1 should not generate a replacement header yet.

Phase 2 should choose one of these approaches:
- `script/build.py Cute` defines feature flags for the active build profile and emits a handwritten `CuteConfig.h`
- `src/Cute/Cute.h` includes a stable configuration header owned by the Cute assembly
- package `.upp` `flags` and build-script logic replace simple boolean `CONFIG_*` switches where possible

## Metadata Group
These values describe product identity and should move into Cute assembly startup/about metadata:
- `PROJECT_TITLE`
- `PROJECT_NAME`
- `PROJECT_VERSION`
- `PROJECT_DESCRIPTION`
- `PROJECT_HOMEPAGE_URL`
- `PROJECT_COPYRIGHT`
- `PROJECT_DOMAIN`

Likely future homes:
- startup/about window code under `src/AudioMaster`
- assembly/build metadata under `src/Cute`

## Install/Layout Group
These are packaging concerns, not runtime logic:
- `CONFIG_PREFIX`
- `CONFIG_BINDIR`
- `CONFIG_LIBDIR`
- `CONFIG_DATADIR`
- `CONFIG_MANDIR`

These should be handled by packaging/install tooling in phase 2 or later, not spread across runtime code.

## Build/Platform Group
These shape compile behavior:
- `CONFIG_DEBUG`
- `HAVE_SIGNAL_H`
- `CONFIG_FLOAT32`
- `CONFIG_ROUND`
- `CONFIG_STACKTRACE`
- `CONFIG_WAYLAND`

These likely become:
- build-script options
- platform guards in Cute-owned config headers
- assembly-specific flags

## Library/Backend Group
These are external capability toggles:
- audio/runtime: `CONFIG_LIBJACK`, `CONFIG_LIBASOUND`, `CONFIG_LIBSNDFILE`, `CONFIG_LIBVORBIS`, `CONFIG_LIBMAD`, `CONFIG_LIBSAMPLERATE`, `CONFIG_LIBRUBBERBAND`, `CONFIG_LIBRUBBERBAND_R3`, `CONFIG_LIBAUBIO`, `CONFIG_MINIBPM`, `CONFIG_LIBLO`, `CONFIG_LIBZ`
- plugin/lv2 stack: `CONFIG_LIBLILV`, `CONFIG_LILV_FILE_URI_PARSE`, `CONFIG_LILV_WORLD_UNLOAD_RESOURCE`, `CONFIG_LIBSUIL`, `CONFIG_SUIL_INSTANCE_GET_HANDLE`, `CONFIG_LADSPA`, `CONFIG_DSSI`, `CONFIG_VST2`, `CONFIG_VESTIGE`, `CONFIG_VST3`, `CONFIG_CLAP`, and the `CONFIG_LV2_*` family
- session/host integration: `CONFIG_JACK_SESSION`, `CONFIG_JACK_METADATA`, `CONFIG_JACK_PORT_RENAME`, `CONFIG_NSM`, `CONFIG_XUNIQUE`
- UI style: `CONFIG_GRADIENT`

These should not be blindly copied. They need package ownership:
- `AudioCore` / `Devices` for runtime audio backends
- `VSTHost` / `PluginABI` for plugin APIs
- `AudioMaster` / `Theme` for UI-facing switches
- `Cute` for top-level feature selection and build exposure

## LV2 Subfeature Inventory
The original template enumerates many LV2 capability flags. That means the legacy codebase expects fine-grained capability detection rather than a single on/off switch.

Phase 2 implication:
- `PluginABI/LV2` and `VSTHost` should own the final mapping
- the future Cute config should preserve subfeature granularity where code paths depend on it

## Recommended Cute Config Strategy
1. Keep one Cute-owned master config header, likely `src/Cute/CuteConfig.h`.
2. Restrict package-level preprocessor branching to cases where runtime abstraction is impossible.
3. Prefer capability wrappers in `Devices`, `AudioCore`, and `VSTHost` over scattering raw `CONFIG_*` checks everywhere.
4. Let `script/build.py Cute` decide which external dependency set is active and generate or select the final configuration.

## Manifest Notes For Later
When phase 2 begins:
- add the future `CuteConfig.h` to `src/Cute/Cute.upp`
- keep generated-vs-handwritten config decisions inside Cute assembly tooling
- avoid mirroring the full CMake template verbatim unless a code path truly requires it
