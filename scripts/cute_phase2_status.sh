#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
PHASE2_DIR="$ROOT_DIR/plan/cute/phase2"
RUNTIME_DIR="$ROOT_DIR/docs/runtime-smoke"
OUT_DIR="$ROOT_DIR/docs/phase2"
OUT_FILE="$OUT_DIR/cute-phase2-status.md"

mkdir -p "$OUT_DIR"

build_status="unknown"
if (cd "$ROOT_DIR" && script/build.py -j2 Cute >/tmp/cute_phase2_status_build.log 2>&1); then
  build_status="ok"
else
  build_status="failed"
fi

runtime_count="n/a"
if [ -x "$ROOT_DIR/scripts/cute_runtime_smoke.sh" ]; then
  (cd "$ROOT_DIR" && scripts/cute_runtime_smoke.sh >/tmp/cute_phase2_status_smoke.log 2>&1 || true)
  runtime_count=$(awk -F': ' '/Critical warning line count:/ {print $2}' "$RUNTIME_DIR/cute-runtime-summary.md" | tr -d '[:space:]')
  if [ -z "$runtime_count" ]; then
    runtime_count="0"
  fi
fi

patch_status="unknown"
if [ -x "$ROOT_DIR/scripts/apply_aiupp_gtk_unified_patch.sh" ]; then
  patch_status=$(cd "$ROOT_DIR" && scripts/apply_aiupp_gtk_unified_patch.sh status || echo unknown)
fi

total_tasks=$(find "$PHASE2_DIR" -mindepth 2 -maxdepth 2 -type f -name 'task.md' | wc -l | tr -d '[:space:]')
done_tasks=$( (rg -n "^# Status: DONE" "$PHASE2_DIR" -g 'task.md' || true) | wc -l | tr -d '[:space:]' )
in_progress_tasks=$( (rg -n "^# Status: IN_PROGRESS" "$PHASE2_DIR" -g 'task.md' || true) | wc -l | tr -d '[:space:]' )
todo_tasks=$( (rg -n "^# Status: TODO" "$PHASE2_DIR" -g 'task.md' || true) | wc -l | tr -d '[:space:]' )

latest_commits=$(cd "$ROOT_DIR" && git log --oneline -n 5)

ts="$(date -u +%Y-%m-%dT%H:%M:%SZ)"

{
  echo "# Cute Phase 2 Status"
  echo
  echo "- Timestamp (UTC): $ts"
  echo "- Build status: $build_status"
  echo "- Runtime critical warning count (latest smoke): $runtime_count"
  echo "- ai-upp GTK patch status: $patch_status"
  echo
  echo "## Task Summary"
  echo "- Total tasks: $total_tasks"
  echo "- DONE: $done_tasks"
  echo "- IN_PROGRESS: $in_progress_tasks"
  echo "- TODO: $todo_tasks"
  echo
  echo "## Task Status Lines"
  rg -n "^# Status:" "$PHASE2_DIR" -g 'task.md' || true
  echo
  echo "## Recent Commits"
  echo '```text'
  echo "$latest_commits"
  echo '```'
} > "$OUT_FILE"

echo "Phase-2 status written: $OUT_FILE"
