# Conversion Note: `doc/CMakeLists.txt`

## Source
- `tmp/k/src/doc/CMakeLists.txt`

## Target
- `src/Cool/doc/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Vincent PINON <vincent.pinon@laposte.net>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  doc/documentchecker.cpp
  doc/dcresolvedialog.cpp
  doc/documentcheckertreemodel.cpp
  doc/documentvalidator.cpp
  doc/kdenlivedoc.cpp
  doc/kthumb.cpp
  doc/docundostack.cpp
  PARENT_SCOPE)


```
