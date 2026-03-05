# Conversion Note: `lib/CMakeLists.txt`

## Source
- `tmp/k/src/lib/CMakeLists.txt`

## Target
- `src/Cool/lib/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-FileCopyrightText: 2012 Simon A. Eugster (Granjow) <simon.eu@gmail.com>
# SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL

add_subdirectory(audio)
add_subdirectory(external)
set(kdenlive_SRCS
  ${kdenlive_SRCS}
  lib/qtimerWithTime.cpp
  PARENT_SCOPE)


```
