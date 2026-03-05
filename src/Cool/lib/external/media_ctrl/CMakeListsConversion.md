# Conversion Note: `lib/external/media_ctrl/CMakeLists.txt`

## Source
- `tmp/k/src/lib/external/media_ctrl/CMakeLists.txt`

## Target
- `src/Cool/lib/external/media_ctrl/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Vincent Pinon <vpinon@kde.org>

if(HAVE_LINUX_INPUT_H)
  include_directories(${CMAKE_BINARY_DIR})
  add_library(media_ctrl STATIC mediactrl.c)
  set_property(TARGET media_ctrl PROPERTY C_STANDARD 99)
endif()

```
