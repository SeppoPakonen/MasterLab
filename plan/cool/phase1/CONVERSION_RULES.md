# Cool Phase 1 Conversion Rules

## Mandatory Rules
- Read the kdenlive source file manually before converting it.
- Preserve the same main classes, functions, and approximate amount of code as the original source.
- Convert framework usage from Qt/kdenlive conventions to Ultimate++ conventions and repository package/header rules.
- Write converted result into `src/Cool` in this phase.
- Do not compile, link, or fix downstream compile errors in this phase.

## Naming Rules
- Do not use camelCase in converted code.
- Class names, struct names, enum names, and function names use `CapitalCase`.
- Variables, data members, parameters, locals, and free-standing state names use `lower_underscore`.
- File names for converted outputs use `CapitalCase`.
- Converted implementation units must use `.cpp` extension; do not create `.c` files in `src/Cool`.
- Do not keep `Kdenlive` product naming in converted code; use `Cool` or `MusicEditor` naming.

## U++ Conventions To Apply
- Main package header owns package includes.
- Non-main headers should not add real `#include` directives except inline `.hpp` includes where required.
- `.cpp` files should include only package main header once package wiring is stable.
- Use U++ containers and RAII-oriented ownership.
- Add `typedef <Class> CLASSNAME;` for classes using `THISBACK` macros.

## Output Expectations
- Converted files stay recognisably equivalent to source counterparts.
- QML/UI/XML-like source artifacts are translated into U++-oriented equivalents or conversion notes when direct code mapping is not practical.
- Build-system metadata is translated into Cool assembly/package notes rather than copied verbatim.

## Verification Rules (MANDATORY)
- **Anti-Stubbing**: Do not wrap core class logic in `#if 0`. If a section cannot be converted yet, it must be marked with `// TODO: U++ Migration`.
- **Naming Enforcement**: Any file containing `camelCase` variables or `kdenlive` namespaces will be rejected in the audit.
- **Header Purity**: The goal is to move logic into U++ containers (`Vector`, `Index`, `VectorMap`) and remove the need for `Cool.h` shims unit-by-unit.
- **Audit Step**: Every 10 converted files must undergo a "Surface Audit" to ensure the `CapitalCase` naming and `lower_underscore` rules are being applied.

## Audit Script Requirement
- A script will be used to count lines of active code vs. commented code to ensure "Approximate code volume" rules are met.
