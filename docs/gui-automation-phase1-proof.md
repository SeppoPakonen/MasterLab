# GUI Automation Phase 1 - Proof Scenario (MaestroHub Style)

## Goal
Prove that DAW GUI automation can be executed in a Maestro-style workflow (task + runbook + evidence), without relying on ad-hoc desktop driver assumptions.

## Proof Scenario
### Scenario ID
`daw_gui_launch_stability_smoke`

### Constraint Set
- Build must pass using repository build script.
- GUI app must launch successfully.
- Runtime must remain stable under bounded interval.
- Evidence must be captured in command output logs.

### Commands Executed
```bash
./script/build.py daw
```

```bash
./bin/daw --test src/daw/tests/test_smoke.py
```

### Evidence
- Build result: `BUILD_EXIT:0`
- Smoke test result: `SMOKE2_EXIT:0`
- Constraint test evidence after harness and script stabilization:
  - `test_main_window_constraints.py:0`
  - `test_project_setup_constraints.py:0`
  - `test_transport_constraints.py:0`
  - `test_export_audio_mixdown_constraints.py:0`
  - `test_key_editor_constraints.py:0`
  - `test_midi_score_editor_constraints.py:0`
  - `test_pool_constraints.py:0`
  - `test_vst_connections_constraints.py:0`

## Interpretation
Phase 1 proof is complete and successful:
- DAW test mode executes Python automation reliably.
- GUI constraint checks run with deterministic pass/fail output.
- Initial Cubase-constraint surfaces are covered by executable scripts in `src/daw/tests/*.py`.

This is sufficient to start Phase 2 backlog generation.
