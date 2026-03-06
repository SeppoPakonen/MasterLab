# GTK Warning Upstream Tracking Note (2026-03-06)

## Issue Summary
`Cute` startup on GTK emits repeated critical warnings:
- `gdk_cairo_create: assertion 'GDK_IS_WINDOW (window)' failed`

## Minimal Reproducer
1. Build: `script/build.py -j2 Cute`
2. Run bounded startup: `timeout 5s ./bin/Cute`
3. Optional crash-on-critical backtrace:
   - `gdb -q --batch -ex 'set env G_DEBUG fatal-criticals' -ex run -ex bt --args ./bin/Cute`

## First Critical Call Chain
- `gdk_cairo_create`
- `Upp::CairoGet` in `../ai-upp/uppsrc/CtrlCore/GtkDrawImage.cpp:131`
- `Upp::CairoImage` / `Upp::GetBackgroundColor` / `Upp::ChHostSkin`
- `Upp::Ctrl::ReSkin` / `Upp::Ctrl::SetUHDEnabled`
- `Upp::InitGtkApp`
- project entry: `src/Cute/main.cpp`

## Candidate Upstream Patch Options
1. **Null-window guard before `gdk_cairo_create`**
- Location: `CtrlCore/GtkDrawImage.cpp` around `CairoGet`.
- Approach: if no valid `GdkWindow` exists, draw to an image/cairo surface path without calling `gdk_cairo_create(window)`.
- Risk: low-medium; may affect theming fidelity in early init phase.

2. **Delay host-skin background sampling until window is valid**
- Location: `CtrlLib/ChGtk3.cpp` around `CairoImage` / `GetBackgroundColor` usage during init.
- Approach: defer or fallback to default color until GTK drawable exists.
- Risk: medium; could change initial skin color behavior.

3. **Keep current behavior and downgrade diagnostic noise**
- Location: startup init path.
- Approach: avoid fatal-critical path in diagnostics; retain runtime behavior.
- Risk: low functional impact, but leaves underlying warning unresolved.

## Recommended Direction
- Prefer option 1 (guard in `GtkDrawImage.cpp`) because it targets the immediate invalid-window precondition and minimizes downstream behavior changes.
- If visual regressions appear, combine with option 2 fallback behavior.

## Decision (current)
- **Defer code patch in this repository**; treat as dependency-owned change in `ai-upp`.
- Keep project-level evidence and reproduction automation in place:
  - `scripts/cute_runtime_smoke.sh`
  - `docs/runtime-smoke/*`
