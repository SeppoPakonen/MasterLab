# Conversion Note: `audiomixer/CMakeLists.txt`

## Source
- `tmp/k/src/audiomixer/CMakeLists.txt`

## Target
- `src/Cool/audiomixer/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Jean-Baptiste Mardelle <jb@kdenlive.org>

add_subdirectory(audiolevels)

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  audiomixer/mixerwidget.cpp
  audiomixer/mixermanager.cpp
  audiomixer/audioslider.cpp
  audiomixer/mixerseparator.cpp
  PARENT_SCOPE)



```
