# Conversion Note: `library/CMakeLists.txt`

## Source
- `tmp/k/src/library/CMakeLists.txt`

## Target
- `src/Cool/library/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Jean-Baptiste Mardelle <jb@kdenlive.org>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  library/librarywidget.cpp
  PARENT_SCOPE)

```
