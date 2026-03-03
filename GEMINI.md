# MasterLab Project Rules

## GUI Development and Constraints
- **MANDATORY**: All GUI development in MasterLab MUST implement and utilize the `.ugui` logical constraint system for architectural and functional verification during development and testing.
- All new packages MUST include a `.ugui` file defining mandatory components, layout hierarchy, and architectural mandates (e.g., no bitmap skinning).
- Verification via `--test-gui` or equivalent should be part of the standard testing workflow.
- Refer to `docs/Gui-Constraints.md` for system details and syntax.
