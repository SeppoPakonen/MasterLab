# Task: GUI Constraint Validation

This task involves defining and verifying logical constraints for the `PitchVocalSuite` GUI using the `.ugui` system.

## Objective

To ensure that the `PitchVocalSuite` GUI strictly adheres to the requirements defined in the bootstrap document and architectural mandates.

## Key Actions

1.  **Define Constraints (`PitchVocalSuite.ugui`):** [DONE]
    -   Mandatory visibility of `TopBar`, `GraphEditor`, and `WaveformStrip`.
    -   Requirement for U++ native controls (no skinning).
    -   Verification of core controls (`algorithm`, `correctionSpeed`, `vibratoAmount`).
2.  **Integrate Validation into CLI:**
    -   Add `--test-gui` flag to `PitchVocalSuite` CLI.
    -   Ensure it triggers the `ugui` loading logic.
3.  **Validation Run:**
    -   Run the application with constraints and analyze logs for violations.

## Acceptance Criteria

1.  A `.ugui` file exists with meaningful logical constraints.
2.  The application can be launched with GUI validation active.
3.  Architectural violations (like bitmap skinning) are correctly detected if present.

## Risks

- **Constraint Complexity:** Writing overly complex logical statements might lead to false positives. (Mitigation: Start with simple visibility and type checks).
- **Runtime Overhead:** Continuous validation might impact UI performance. (Mitigation: Only enable validation during testing/CI).
