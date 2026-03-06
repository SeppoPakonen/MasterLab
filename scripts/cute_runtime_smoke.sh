#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BIN="$ROOT_DIR/bin/Cute"
OUT_DIR="$ROOT_DIR/docs/runtime-smoke"
RUNTIME_LOG="$OUT_DIR/cute-runtime.log"
GDB_LOG="$OUT_DIR/cute-gdb-bt.log"
SUMMARY="$OUT_DIR/cute-runtime-summary.md"

mkdir -p "$OUT_DIR"

if [ ! -x "$BIN" ]; then
  echo "Missing executable: $BIN" >&2
  echo "Build first with: script/build.py -j2 Cute" >&2
  exit 1
fi

start_ts="$(date -u +%Y-%m-%dT%H:%M:%SZ)"

set +e
timeout 5s "$BIN" >"$RUNTIME_LOG" 2>&1
runtime_exit=$?
set -e

gdb -q --batch \
  -ex 'set env G_DEBUG fatal-criticals' \
  -ex run \
  -ex bt \
  --args "$BIN" >"$GDB_LOG" 2>&1 || true

warn_count=$(rg -c "Gdk-CRITICAL|Gtk-CRITICAL|CRITICAL" "$RUNTIME_LOG" || true)

{
  echo "# Cute Runtime Smoke Summary"
  echo
  echo "- Timestamp (UTC): $start_ts"
  echo "- Command: timeout 5s ./bin/Cute"
  echo "- Exit code: $runtime_exit"
  echo "- Critical warning line count: $warn_count"
  echo "- Runtime log: docs/runtime-smoke/cute-runtime.log"
  echo "- GDB backtrace log: docs/runtime-smoke/cute-gdb-bt.log"
  echo
  echo "## First Runtime Lines"
  sed -n '1,20p' "$RUNTIME_LOG"
  echo
  echo "## First Backtrace Lines"
  sed -n '1,40p' "$GDB_LOG"
} > "$SUMMARY"

echo "Runtime smoke artifacts written to: $OUT_DIR"
