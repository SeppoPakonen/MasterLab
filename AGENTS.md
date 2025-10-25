# AGENTS — Project Architecture & Codex Integration

## Overview
This repository contains an audio editor and mastering tool built in **C++** using the **Ultimate++ framework**.  
All source packages follow the U++ assembly/package conventions.

## Directory Layout
```
uppsrc/        ← Ultimate++ core sources (external dependency)
src/               ← Main program assembly (packages with .upp files)
unittst/           ← Unit test assembly
tutorials/         ← Tutorial projects (for learning and experiments)
reference/         ← Reference code and sample implementations

```

## Package Rules
- Each package is a directory containing a `.upp` file named identically to the folder (e.g., `Core/Core.upp`).
- Each `.upp` file lists *all* source files in that package.
- Packages can reference each other through U++ assembly definitions.
- Assemblies are declared within Ultimate++ IDE (TheIDE) or configuration files.

## Build Rules
- Initially, **no Makefiles or CMake**.  
- All builds are managed via Ultimate++ assemblies.  
- Optional CMake or Makefile integration may be added later for CI or cross-platform builds.

## Codex Tasks
Codex acts as a commentary and assistant system to:
- Generate and maintain `.upp` package lists  
- Propose internal documentation  
- Suggest test cases in `unittst/`  
- Create initial source file templates  