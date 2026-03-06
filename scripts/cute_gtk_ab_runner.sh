#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
GTK_FILE="$ROOT_DIR/../ai-upp/uppsrc/CtrlCore/GtkDrawImage.cpp"
SMOKE_SCRIPT="$ROOT_DIR/scripts/cute_runtime_smoke.sh"
OUT_DIR="$ROOT_DIR/docs/runtime-smoke"
REPORT="$OUT_DIR/cute-gtk-ab-runner-summary.md"
mkdir -p "$OUT_DIR"

if [ ! -f "$GTK_FILE" ]; then
  echo "Missing dependency file: $GTK_FILE" >&2
  exit 1
fi
if [ ! -x "$SMOKE_SCRIPT" ]; then
  echo "Missing smoke script: $SMOKE_SCRIPT" >&2
  exit 1
fi

backup="$(mktemp /tmp/GtkDrawImage.cpp.abrunner.XXXXXX)"
cp "$GTK_FILE" "$backup"
restore() {
  cp "$backup" "$GTK_FILE"
  rm -f "$backup"
}
trap restore EXIT

count_from_summary() {
  awk -F': ' '/Critical warning line count:/ {print $2}' "$OUT_DIR/cute-runtime-summary.md" | tr -d '[:space:]'
}

run_smoke_count() {
  "$SMOKE_SCRIPT" >/dev/null 2>&1
  local n
  n="$(count_from_summary)"
  if [ -z "$n" ]; then
    n=0
  fi
  echo "$n"
}

build_cute() {
  (cd "$ROOT_DIR" && script/build.py -j2 Cute >/dev/null 2>&1)
}

start_ts="$(date -u +%Y-%m-%dT%H:%M:%SZ)"

build_cute
baseline="$(run_smoke_count)"

# Minimal local trial patch: disable unsafe NULL-window cairo creation call.
perl -0pi -e 's/cairo_t \*cr = gdk_cairo_create\(NULL\);[^\n]*/cairo_t *cr = NULL; \/\/ patched by cute_gtk_ab_runner: avoid gdk_cairo_create(NULL)/' "$GTK_FILE"

build_cute
patched="$(run_smoke_count)"

cp "$backup" "$GTK_FILE"
build_cute
restored="$(run_smoke_count)"

{
  echo "# GTK A/B Runner Summary"
  echo
  echo "- Timestamp (UTC): $start_ts"
  echo "- Baseline critical warning count: $baseline"
  echo "- Patched critical warning count: $patched"
  echo "- Restored critical warning count: $restored"
  echo "- Dependency file restored automatically: yes"
  echo
  echo "## Interpretation"
  if [ "$patched" -lt "$baseline" ]; then
    echo "- Patch candidate reduced warning count."
  else
    echo "- Patch candidate did not reduce warning count in this run."
  fi
} > "$REPORT"

echo "A/B report written: $REPORT"
