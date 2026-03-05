# Conversion Note: `titler/CMakeLists.txt`

## Source
- `tmp/k/src/titler/CMakeLists.txt`

## Target
- `src/Cool/titler/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Vincent PINON <vincent.pinon@laposte.net>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  titler/titledocument.cpp
  titler/titlewidget.cpp
  titler/gradientwidget.cpp
  titler/graphicsscenerectmove.cpp
  titler/unicodedialog.cpp
  titler/patternsmodel.cpp
  PARENT_SCOPE)


```
