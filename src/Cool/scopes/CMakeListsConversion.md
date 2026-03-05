# Conversion Note: `scopes/CMakeLists.txt`

## Source
- `tmp/k/src/scopes/CMakeLists.txt`

## Target
- `src/Cool/scopes/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Jean-Baptiste Mardelle <jb@kdenlive.org>

add_subdirectory(colorscopes)
add_subdirectory(audioscopes)
set(kdenlive_SRCS
  ${kdenlive_SRCS}
  scopes/scopemanager.cpp
  scopes/abstractscopewidget.cpp
  PARENT_SCOPE)


```
