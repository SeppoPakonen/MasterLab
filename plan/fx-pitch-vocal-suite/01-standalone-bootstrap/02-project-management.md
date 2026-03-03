# Task: Project Management and MenuBar

This task involves adding a standard menu bar and project file support (load/save) to the standalone `PitchVocalSuite`.

## Objective

To allow users to save their manual pitch correction work (notes) and reload them alongside the associated audio file.

## Key Actions

1.  **Extend `PluginWindow`:** [DONE]
    -   Add `MenuBar` support to the generic plugin hosting window.
2.  **Implement Main Menu:** [DONE]
    -   Add "File" menu with New, Open, Save, Save As, and Exit.
3.  **JSON Serialization:** [DONE]
    -   Implement `Jsonize` for `PitchNote` and `PitchVocalEditor`.
    -   Store `audioPath` and the list of `notes` in a `.pvp` (PitchVocal Project) file.
4.  **CLI Support:** [DONE]
    -   Add `--project <path>` argument to open a project file on startup.

## Acceptance Criteria

1.  The standalone application displays a menu bar. [DONE]
2.  Users can save their work to a `.pvp` file and reload it. [DONE]
3.  Opening a project automatically loads the associated audio file. [DONE]

## Risks

- **Path Portability:** Storing absolute paths to audio files might break if the files are moved. (Mitigation: Use relative paths in the future).
