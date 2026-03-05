# Conversion Note: `monitor/scopes/CMakeLists.txt`

## Source
- `tmp/k/src/monitor/scopes/CMakeLists.txt`

## Target
- `src/Cool/monitor/scopes/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Jean-Baptiste Mardelle <jb@kdenlive.org>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  monitor/scopes/scopewidget.cpp
  monitor/scopes/monitoraudiolevel.cpp
  monitor/scopes/audiographspectrum.cpp
  monitor/scopes/sharedframe.cpp
PARENT_SCOPE)

```
