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



## Ultimate++ Package Conventions

The **Ultimate++ (U++)** framework organizes all code into *assemblies* and *packages*.

Each **package** is a directory containing a `.upp` file with the same name as the directory itself:
```

abc/abc.upp

```

Every package also has a **main header**, named after the package:
```

abc/abc.h

```
This main header is the **only** header that should include other headers.  
Other `.h` files within the same package must not contain `#include` directives except for **inline includes** (see below).


### Headers
Don't use #pragma once inheaders but the style of

```
#ifndef _daw_daw_h_
#define _daw_daw_h_

// all content of the file

#endif
```

Don't have dependency #include statements in non-main headers.

You may add "// #include "...dependency.." as comment for clarity, but they are included elsewhere and the classes are present without additional #include statement.

The compiler already sees classes, but YOU don't. E.g. don't add that "#include <AudioCore/AudioCore.h>" in "src/AudioFX/Limiter.h" for compiler, but add it as COMMENT for YOU only.

And I repeat, this doesn' change any architectural changes. This ONLY affects preprocessor. The ONLY problem is YOU not understanding how headers and code dependencies are included.

### Forward declaration
Do all forward declarations in the beginning of main-header, so they don't need to be forward declared in every header.

AI may add comments, if it looks otherwise, that no classes have been included yet, since we don't use inside-non-main-header inclusions anymore.


### Inline Includes
If template classes or inline functions require definitions within headers, these may be placed in `.hpp` files.  
Such `.hpp` files are included where necessary using inline includes:
```

#include "template_impl.hpp" // allowed only for inline definitions

```

### Inclusion Rules
- **Only the main header (`package/package.h`)** includes other headers.
- **All `.cpp` files** in a package must include *only the main header* of their package.
- Headers from *other packages* must be included by their main headers only (e.g. `#include <AudioCore/AudioCore.h>`).

### Package Dependencies (`uses`)
If a package uses another package’s main header, it must explicitly declare this dependency in its `.upp` file via the `uses(...)` section.

For example:
```

uses
Core
Draw
CtrlCore
CtrlLib
AudioCore
AudioGraph

```

This ensures Ultimate++ (TheIDE) correctly manages compilation order, linking, and visibility across packages.

### Enforcement
When writing or maintaining code:
- Move all `#include` statements from non-main headers into the corresponding main header.
- Ensure `.cpp` files only include their package’s main header.
- Maintain clear `uses(...)` relationships between packages.
- Other than main headers doesn't need to be self-contained, since implementation files only use packet's main header.

### Summary
U++ packages behave as independent modular units.  
Their boundaries are defined by `.upp` manifests and main headers.  
This convention guarantees consistency, avoids circular dependencies, and makes the codebase predictable for both Codex and human developers.
```

