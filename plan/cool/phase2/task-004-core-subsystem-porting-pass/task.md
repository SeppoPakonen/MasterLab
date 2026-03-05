# Task: Core Subsystem Porting Pass
# Status: TODO

## Objective
Port `src/Cool/Core.cpp` and immediate dependencies so compilation no longer depends on unresolved Qt/KDE runtime types.

## Scope
- Address first failing symbols in `Core.cpp` (`Core`, `LinuxPackageType`, `QUrl`, `QString`, `QStringList`, etc.).
- Introduce compile-safe Cool/U++ alternatives or explicit staged stubs.
- Keep incremental: compile-first, then continue with next failures.

## Definition of Done
- [ ] `Core.cpp` compiles in current build mode.
- [ ] Next failing subsystem is identified and documented.
