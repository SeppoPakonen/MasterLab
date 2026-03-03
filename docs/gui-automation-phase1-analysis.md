# GUI Automation Phase 1 - Maestro/MaestroHub Analysis

## Summary
Phase 1 follows the Maestro planning style and MaestroHub automation model.

- Plan structure used here: `plan/<track>/<task>/*.md`
- Automation style reference: runbook-like steps, explicit expected outcomes, and evidence logging (from MaestroHub UX evaluation and automation output patterns).
- DAW automation runtime: `./bin/daw --test <script.py>` with Python scripts in `src/daw/tests/*.py`.

## Source References Used
- `~/Dev/ai-upp/uppsrc/Maestro/PlanCommand.cpp`
- `~/Dev/ai-upp/uppsrc/Maestro/PlanParser.cpp`
- `~/Dev/ai-upp/uppsrc/MaestroHub/UXEvaluation.cpp`
- `~/Dev/ai-upp/uppsrc/MaestroHub/main.cpp`

## `*.ugui` Inventory (Requested)
Search target: `../ai-upp/uppsrc`

Result: no `*.ugui` files found.

Command:
```bash
find ../ai-upp/uppsrc -type f -name '*.ugui'
```

## Maestro-Compatible Planning Interpretation
From Maestro parser/command behavior:
- Tracks and phases are directory-based groupings.
- Tasks are markdown files with machine-parsable status via `# Status: ...`.
- Task lifecycle supports `todo`, `in_progress`, `done`, `blocked` semantics.

For this repository, phase separation is represented as separate tracks under `plan/gui-automation/`.

## MaestroHub-Compatible GUI Automation Interpretation
From MaestroHub UI automation/evaluation surfaces:
- Tests are modeled as named scenarios with explicit status.
- Execution is run-action driven (`Run Test`) and produces visible automation output/evidence.
- Flow is runbook-like: action steps + expected outcomes.

This phase therefore documents one DAW proof scenario in runbook form and records command evidence.

## Initial DAW Automation File (Python)
Per Maestro-style convention, GUI automation tests are Python files under the package test folder.

Initial file:
- `src/daw/tests/test_smoke.py`

Expected invocation style:
```bash
./bin/daw --test src/daw/tests/test_smoke.py
```

## Phase-1 Output Snapshot
- Test runner support implemented in DAW main entry with ByteVM + automation bindings.
- Constraint scripts implemented for:
  - main window
  - project setup
  - transport
  - export audio mixdown
  - key editor
  - MIDI score editor
  - pool
  - VST connections
- These scripts currently pass in the local environment and provide the starting baseline for phase-2 expansion.
