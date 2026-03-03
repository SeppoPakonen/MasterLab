# GUI Constraint System (.ugui)

The MasterLab repository utilizes a logical constraint system powered by the U++ `CtrlCore` and `AI/Logic` components to ensure that Graphical User Interfaces (GUIs) fulfill specific architectural and functional requirements at runtime.

## Purpose

GUI constraints are defined in `.ugui` files. These files contain a set of logical statements that describe the expected state, hierarchy, and properties of UI components. The system is used to:
- Verify that mandatory UI elements are present and visible.
- Ensure proper component relationships (e.g., "if A is visible, B must also be visible").
- Validate architectural mandates (e.g., "UI must not use bitmap skinning").
- Assist in automated testing and AI-driven GUI generation.

## Syntax

The `.ugui` files use a declarative logic-based syntax. Common predicates and operators include:

### Predicates
- `VISIBLE(ctrl)`: True if the control `ctrl` is visible.
- `ENABLED(ctrl)`: True if the control `ctrl` is enabled.
- `BUTTON(ctrl)`: True if the control `ctrl` is a button.
- `LABEL(ctrl)`: True if the control `ctrl` is a label.
- `HAS_PARENT(child, parent)`: True if `child` is a sub-component of `parent`.
- `IS_TYPE(ctrl, type)`: True if `ctrl` is of a specific class type.
- `IS_SKINNED(ctrl)`: Returns property of skinning (should be false for MasterLab).

### Logical Operators
- `and`: Logical conjunction.
- `or`: Logical disjunction.
- `not`: Logical negation.
- `implies`: Logical implication (if A then B).

## Usage

Applications load `.ugui` files at startup. By default, the system looks for a file named `<executable_name>.ugui` in the same directory as the executable or in the current working directory.

You can also specify a custom path via the command line:
```bash
./PitchVocalSuite --ugui path/to/constraints.ugui
```

During execution, the `CtrlCore` logic engine analyzes the runtime UI tree against these constraints and logs violations.

## PitchVocalSuite Constraints

The `PitchVocalSuite` must adhere to the following constraints defined in `PitchVocalSuite.ugui`:
- Presence of `PitchVocalTopBar`, `PitchGraphEditor`, and `WaveformStrip`.
- Correct vertical layout hierarchy.
- Adherence to U++ native-like controls without bitmap skinning.
