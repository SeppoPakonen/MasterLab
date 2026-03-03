# Build System Observations

This document details the current state of the U++ build system for `PitchVocalSuite`.

## Tooling

- **`umk`:** The command-line builder for U++.
- **`script/build.py`:** A Python wrapper for `umk` that simplifies target selection and flags.

## Build Wrapper Analysis (`script/build.py`)

- `src_root` is hardcoded to `src/`.
- Target resolution logic:
    1.  If target is a `.upp` path, use it.
    2.  Check `src/{target}/{target}.upp`.
    3.  Recursive search for `{target}.upp` under `src/`.

## Challenges for `PitchVocalSuite`

- `PitchVocalSuite` is currently located under `effects/`, which is outside of `src/`.
- The command `script/build.py PitchVocalSuite` will fail as it only searches `src/`.

## Proposed Solutions

1.  **Modify `build.py`:** Update `resolve_upp_path` to include `effects/`, `instruments/`, and other top-level package directories in its search path.
2.  **Move Packages:** Reorganize the directory structure so all buildable packages are under `src/`.
3.  **Use Full Paths:** Always invoke `build.py` with the full path to the `.upp` file (e.g., `script/build.py effects/PitchVocalSuite/PitchVocalSuite.upp`). This is less convenient.

## Preferred Path

**Solution 1 (Modify `build.py`)** is preferred as it maintains the project's organizational structure while improving tool usability.
