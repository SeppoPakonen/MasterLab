#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
GTK_FILE="$ROOT_DIR/../ai-upp/uppsrc/CtrlCore/GtkDrawImage.cpp"

if [ $# -ne 1 ]; then
  echo "Usage: $0 <apply|revert|status>" >&2
  exit 2
fi

mode="$1"

if [ ! -f "$GTK_FILE" ]; then
  echo "Missing file: $GTK_FILE" >&2
  exit 1
fi

orig='cairo_t \*cr = gdk_cairo_create\(NULL\);'
patch='cairo_t *cr = NULL; // patched by toggle_aiupp_gtk_patch: avoid gdk_cairo_create(NULL)'

has_orig() {
  rg -q "$orig" "$GTK_FILE"
}

has_patch() {
  rg -q "patched by toggle_aiupp_gtk_patch" "$GTK_FILE"
}

case "$mode" in
  status)
    if has_patch; then
      echo "patched"
    elif has_orig; then
      echo "original"
    else
      echo "unknown"
      exit 1
    fi
    ;;
  apply)
    if has_patch; then
      echo "already patched"
      exit 0
    fi
    if ! has_orig; then
      echo "cannot apply: expected original line not found" >&2
      exit 1
    fi
    perl -0pi -e 's/cairo_t \*cr = gdk_cairo_create\(NULL\);[^\n]*/cairo_t *cr = NULL; \/\/ patched by toggle_aiupp_gtk_patch: avoid gdk_cairo_create(NULL)/' "$GTK_FILE"
    echo "patched"
    ;;
  revert)
    if has_orig; then
      echo "already original"
      exit 0
    fi
    if ! has_patch; then
      echo "cannot revert: expected patched marker not found" >&2
      exit 1
    fi
    perl -0pi -e 's/cairo_t \*cr = NULL; \/\/ patched by toggle_aiupp_gtk_patch: avoid gdk_cairo_create\(NULL\)/cairo_t *cr = gdk_cairo_create(NULL);/' "$GTK_FILE"
    echo "reverted"
    ;;
  *)
    echo "invalid mode: $mode" >&2
    exit 2
    ;;
esac
