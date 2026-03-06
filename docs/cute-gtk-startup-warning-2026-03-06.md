# Cute GTK Startup Warning Investigation (2026-03-06)

## Reproduction
- Command: `timeout 5s ./bin/Cute`
- Observed warning spam:
  - `Gdk-CRITICAL **: gdk_cairo_create: assertion 'GDK_IS_WINDOW (window)' failed`

## Backtrace Capture
- Command:
  - `gdb -q --batch -ex 'set env G_DEBUG fatal-criticals' -ex run -ex bt --args ./bin/Cute`
- First warning call chain (trimmed):
  - `gdk_cairo_create`
  - `Upp::CairoGet` at `ai-upp/uppsrc/CtrlCore/GtkDrawImage.cpp:131`
  - `Upp::CairoImage` / `Upp::GetBackgroundColor` / `Upp::ChHostSkin`
  - `Upp::Ctrl::ReSkin` / `Upp::Ctrl::SetUHDEnabled`
  - `Upp::InitGtkApp`
  - `main` at `src/Cute/main.cpp`

## Decision
- Root source is in external dependency layer (`ai-upp` CtrlCore/CtrlLib GTK skin init path), not in project `src/*` logic.
- No safe in-project patch identified that removes this warning without modifying U++ dependency behavior.
- Keep current project code unchanged and track this as dependency-side hardening work.

## Impact
- `Cute` build and link are successful.
- Runtime warning noise remains on GTK startup; no direct project-side crash was identified in this pass.
