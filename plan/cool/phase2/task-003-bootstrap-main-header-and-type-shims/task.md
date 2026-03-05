# Task: Bootstrap Main Header And Type Shims
# Status: IN PROGRESS

## Objective
Create temporary compile-time bridges for converted Qt/KDE types to unblock staged compilation.

## Scope
- Add interim declarations/adapters in Cool package headers for unresolved symbols used by converted files.
- Keep shims explicit and local to bring-up phase.
- Track every shim for later replacement by real U++ implementations.

## Definition of Done
- [ ] `Cool.h` / related bootstrap headers provide enough scaffolding to compile additional converted translation units.
- [ ] Shim usage is documented for later cleanup.
