# Conversion Note: `layouts/CMakeLists.txt`

## Source
- `tmp/k/src/layouts/CMakeLists.txt`

## Target
- `src/Cool/layouts/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: 2025 Kdenlive contributors

set(kdenlive_SRCS
  ${kdenlive_SRCS}
    layouts/layoutmanagement.cpp
    layouts/layoutmanagerdialog.cpp
    layouts/layoutswitcher.cpp
    layouts/layoutcollection.cpp
  PARENT_SCOPE)
```
