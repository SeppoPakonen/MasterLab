# Task: Package Wiring and Dependency Resolution

This task involves configuring the `PitchVocalSuite.upp` file and establishing correct dependency wiring within the MasterLab repository.

## Purpose

To ensure that the `PitchVocalSuite` package can correctly resolve and link against internal and external dependencies.

## Key Actions

1.  **Inspect and Update `PitchVocalSuite.upp`:**
    - Verify existing `uses`.
    - Add needed internal packages (e.g., `AudioAnalysis`).
    - Add any required external U++ packages if available (e.g., `AudioCtrl`).
2.  **Define Mainconfig:**
    - Add a `mainconfig` section to `PitchVocalSuite.upp` for standalone build.
    - Example: `"Standalone" = "GUI";`
3.  **Coordinate with Build Script:**
    - Ensure the build script finds the `.upp` in `effects/PitchVocalSuite/`.

## Acceptance Criteria

1.  The `PitchVocalSuite.upp` file is correctly configured with all necessary `uses`.
2.  The `mainconfig` section exists and is appropriate for a standalone application.
3.  The build system (via updated `script/build.py`) can resolve all dependencies.

## Risks

- **Cyclic Dependencies:** Avoid introducing circular dependencies between packages.
- **Missing External Resources:** If `AudioCtrl` or `SoftAudio` are not found, fallback to internal implementations.
