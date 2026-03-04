# Cute Phase 1 Conversion Rules

## Mandatory Rules
- Read the qtractor source file manually before converting it.
- Preserve the same main classes, functions, and approximate amount of code as the original source.
- Convert framework usage from Qt/qtractor conventions to Ultimate++ conventions and the repository's package/header rules.
- Write the converted result into the suggested `src/*` package so existing stubs become populated.
- Do not try to compile, link, or fix downstream compile errors in this phase.

## Naming Rules
- Do not use camelCase in converted code.
- Class names, struct names, enum names, and function names use `CapitalCase`.
- Variables, data members, parameters, local temporaries, and free-standing state names use `lower_underscore`.
- File names for converted outputs use `CapitalCase`.
- Keep upstream source filenames only when referring to the original qtractor inputs in plan/task documentation.
- Do not keep legacy `QTractor` product naming in converted code; use `Cute` or `MusicEditor` naming instead.

## U++ Conventions To Apply
- Main package header owns package includes.
- Non-main headers should not add real `#include` directives except inline `.hpp` includes when required.
- `.cpp` files should include only their package main header once the package is wired.
- Use U++ containers and RAII-oriented ownership patterns instead of ad-hoc heap ownership.
- Add `typedef <Class> CLASSNAME;` when a class uses `THISBACK`.

## Output Expectations
- The converted file should stay recognisably equivalent to its qtractor source counterpart.
- UI `.ui` files should be converted into the U++ layout/control approach that best matches the target package.
- Meta files like `CMakeLists.txt`, `config.h.cmake`, and `qtractor.qrc` should be translated into Cute assembly/package notes rather than copied verbatim.

## Out Of Scope
- Build fixes.
- Behavioural rewrites beyond what U++ conversion requires.
- Vendor SDK migration for nested third-party trees under `tmp/q/src/`.
