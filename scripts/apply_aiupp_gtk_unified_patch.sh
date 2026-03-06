#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
PARENT_DIR="$(cd "$ROOT_DIR/.." && pwd)"
PATCH_FILE="$ROOT_DIR/docs/patches/ai-upp-gtkdrawimage-null-window-guard.diff"
GTK_FILE="$ROOT_DIR/../ai-upp/uppsrc/CtrlCore/GtkDrawImage.cpp"

if [ $# -ne 1 ]; then
  echo "Usage: $0 <apply|revert|status>" >&2
  exit 2
fi

mode="$1"

if [ ! -f "$PATCH_FILE" ]; then
  echo "Missing patch file: $PATCH_FILE" >&2
  exit 1
fi
if [ ! -f "$GTK_FILE" ]; then
  echo "Missing target file: $GTK_FILE" >&2
  exit 1
fi

case "$mode" in
  status)
    if rg -q "patched by toggle_aiupp_gtk_patch" "$GTK_FILE"; then
      echo "patched"
    else
      echo "original"
    fi
    ;;
  apply)
    (cd "$PARENT_DIR" && patch -p0 --forward < "$PATCH_FILE") >/dev/null || true
    if rg -q "patched by toggle_aiupp_gtk_patch" "$GTK_FILE"; then
      echo "patched"
    else
      echo "apply failed" >&2
      exit 1
    fi
    ;;
  revert)
    (cd "$PARENT_DIR" && patch -R -p0 --forward < "$PATCH_FILE") >/dev/null || true
    if rg -q "patched by toggle_aiupp_gtk_patch" "$GTK_FILE"; then
      echo "revert failed" >&2
      exit 1
    fi
    echo "original"
    ;;
  *)
    echo "invalid mode: $mode" >&2
    exit 2
    ;;
esac
