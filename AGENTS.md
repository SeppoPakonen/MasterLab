# AGENTS — Project Architecture & Codex Integration

## Overview
This repository contains an audio editor and mastering tool built in **C++** using the **Ultimate++ framework**.  
All source packages follow the U++ assembly/package conventions.

Be sure to check how U++ programs are done from "~/upp/uppsrc/ide" package if you are not sure.

## Directory Layout
```
uppsrc/        ← Ultimate++ core sources (external dependency)
src/               ← Main program assembly (packages with .upp files)
effects/           ← Stub effect packages replacing commercial plug-ins
instruments/       ← Stub instrument packages replacing commercial plug-ins
unittst/           ← Unit test assembly
tutorials/         ← Tutorial projects (for learning and experiments)
reference/         ← Reference code and sample implementations

```

## Package Rules
- Each package is a directory containing a `.upp` file named identically to the folder (e.g., `Core/Core.upp`).
- Each `.upp` file lists *all* source files in that package.
- Packages can reference each other through U++ assembly definitions.
- Assemblies are declared within Ultimate++ IDE (TheIDE) or configuration files.
- Every package maintains an `AGENTS.md` at the root of the package directory documenting key classes and responsibilities. List this file first in the package’s `.upp` manifest so the IDE surfaces it at the top of the file tree.

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

The compiler already sees the classes, but YOU don't. For example, don't add "#include <AudioCore/AudioCore.h>" to "src/AudioFX/Limiter.h" for the compiler, add it as a COMMENT just for YOU.

Fix the problems by looking for "\n#include" in ".h" files and if it's not a main header, convert it to a comment. Almost the same applies to c/cpp files: look for "\n#include" in ".cpp" files and if it's not a main header, convert it to a comment, UNLESS it's really only needed in the implementation, which is very possible, but check if it's already in the main header.

And I repeat, this doesn't change any architectural changes. This ONLY affects the preprocessor. The ONLY problem is that YOU don't understand how to include headers and code dependencies.

This means that you can't just add include statements and hope for the best, thinking that everything is fine now that the included headers are chained. You MUST also consider circular dependencies through the main headers. They would have broken silently even with the previous include technique.

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

### Classes
There's no smart-pointers in U++ really, but you should use RAII.
This is not a proper solution:
```
Vector< Ptr<Node> > nodes;
```

Instead this is proper solution:
```
Array<Node> nodes;
```

For "smart-values" you may add raw classes to Value class, and then use proper value-based semantics. But no, there's no valid mid-ground between value-semantics and RAII.

Everything in Vector<> must be trivially copyable, but Array<> doesn't have that requirement. Pointers to Vector<> cannot be trusted almost ever. But you may trust pointers to vector ranges, if you take both begin and end pointers at the beginning. Even that should be used only in very fast loops. You may trust pointers to Array<>, but add additional Ptr/Pte semantics (struct Obj : Pte<Obj> {}; Ptr<Obj> o;) if you must be sure.

If class' methods uses THISBACK macros, then class definition must have e.g. (the class is Node) "typedef Node CLASSNAME;" statement.

So, because we use RAII, avoid using new operator everywhere. If it is being used, it must be contained in RAII containers immediately. It cannot be created just for stack memory, to a pointer in the middle of a function. You will NEVER use pointers for OWNED variables, but if you need to transfer ownership, you may create One<T> wrapper. You will NEVER need to delete values in destructor (unless you are making a container template class).

## Task Execution Protocol

When Codex is instructed to *"work"* or *"execute tasks"*, it must:

1. Open `TASKS.md`.
2. Identify the first item listed under **TODO**.
3. Move that item to **IN PROGRESS** and begin work according to its instructions.
4. Once complete, move the same item to **DONE**.
5. Commit any resulting files or documentation changes.
6. Include commit messages in the format:

   ```
   codex: complete task <task number> — <short description>
   ```

All development tasks must exist within `TASKS.md` and follow this status-tracking system.
No direct implementation tasks are executed unless defined in `TASKS.md`.

## U++ Key System Implementation

When implementing U++ accelerator keys, follow this pattern:

1. Create a `.key` file with KEY(...) macros:
```
KEY(COMMAND_NAME, "Menu Path/Command Name", "Key Sequence")
```

2. Use these macros in source files:
```cpp
#define KEYGROUPNAME "AK"
#define KEYNAMESPACE AKKeys
#define KEYFILE      <ProjectMgmt/AK.key>
#include             <CtrlLib/key_source.h>
```

3. For header files, use:
```cpp
#define KEYGROUPNAME "AK"
#define KEYNAMESPACE AKKeys
#define KEYFILE      <ProjectMgmt/AK.key>
#include             <CtrlLib/key_header.h>
```

This generates appropriate command IDs and access functions that integrate with U++'s menu and accelerator system.

Example from ~/upp/reference/AK/AK.upp:
- The AK.key file uses KEY(...) macros for defining commands
- The AK.h file uses key_header.h to generate accessors
- The system integrates with U++'s menu and accelerator framework
