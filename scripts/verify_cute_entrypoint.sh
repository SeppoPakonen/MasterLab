#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
OUT="$ROOT_DIR/docs/phase2/cute-entrypoint-verification.md"

scripts=(
  "$ROOT_DIR/scripts/cute_runtime_smoke.sh"
  "$ROOT_DIR/scripts/cute_gtk_ab_runner.sh"
  "$ROOT_DIR/scripts/cute_phase2_status.sh"
)

fail=0

{
  echo "# Cute Entrypoint Verification"
  echo
  echo "- Timestamp (UTC): $(date -u +%Y-%m-%dT%H:%M:%SZ)"
  echo
  echo "## Script Checks"

  for s in "${scripts[@]}"; do
    echo "### ${s#$ROOT_DIR/}"
    if [ ! -f "$s" ]; then
      echo "- exists: no"
      echo "- status: FAIL (missing script)"
      fail=1
      continue
    fi
    echo "- exists: yes"

    if rg -q "bin/Cute|\./bin/Cute|BIN=.*Cute" "$s"; then
      echo "- references Cute binary: yes (direct)"
    elif rg -q "cute_runtime_smoke.sh" "$s"; then
      echo "- references Cute binary: yes (via cute_runtime_smoke.sh)"
    else
      echo "- references Cute binary: no"
      fail=1
    fi

    if rg -q "bin/daw|\./bin/daw|daw --test|src/daw/tests" "$s"; then
      echo "- references daw binary: yes"
      echo "- status: FAIL"
      fail=1
    else
      echo "- references daw binary: no"
      echo "- status: PASS"
    fi
    echo
  done

  echo "## Aggregate"
  if [ "$fail" -eq 0 ]; then
    echo "- Result: PASS"
  else
    echo "- Result: FAIL"
  fi
} > "$OUT"

echo "Entrypoint verification written: $OUT"
if [ "$fail" -ne 0 ]; then
  exit 1
fi
