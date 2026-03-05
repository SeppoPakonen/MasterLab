# Conversion Note: `renderpresets/CMakeLists.txt`

## Source
- `tmp/k/src/renderpresets/CMakeLists.txt`

## Target
- `src/Cool/renderpresets/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Julius Künzel <julius.kuenzel@kde.org>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  renderpresets/renderpresetrepository.cpp
  renderpresets/renderpresetmodel.cpp
  renderpresets/tree/renderpresettreemodel.cpp
  PARENT_SCOPE)


```
