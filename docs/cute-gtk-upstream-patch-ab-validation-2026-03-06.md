# GTK Upstream Patch A/B Validation (2026-03-06)

## Setup
- Build command: `script/build.py -j2 Cute`
- Smoke command: `scripts/cute_runtime_smoke.sh`
- Patch target: `../ai-upp/uppsrc/CtrlCore/GtkDrawImage.cpp`

## Measurements
1. Baseline (dependency unpatched)
- Critical warning line count: `246`

2. Patched (local trial)
- Applied change: replace unsafe `gdk_cairo_create(NULL)` path with direct `gdk_pixbuf_get_from_surface(...)` extraction.
- Critical warning line count: `0`

3. Restored baseline
- Restored original dependency file from backup.
- Critical warning line count after restore: `246`

## Conclusion
- The patch candidate removes the observed GTK startup warning spam in this environment.
- Effect is reversible and isolated to dependency code path.
- Recommended next step: apply patch upstream in `ai-upp` and re-run smoke in CI/dev bootstrap.
