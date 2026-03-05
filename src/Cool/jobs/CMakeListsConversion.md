# Conversion Note: `jobs/CMakeLists.txt`

## Source
- `tmp/k/src/jobs/CMakeLists.txt`

## Target
- `src/Cool/jobs/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Jean-Baptiste Mardelle <jb@kdenlive.org>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  jobs/abstracttask.cpp
  jobs/taskmanager.cpp
  jobs/audiolevels/audiolevelstask.cpp
  jobs/audiolevels/generators.cpp
  jobs/cliploadtask.cpp
  jobs/proxytask.cpp
  jobs/stabilizetask.cpp
  jobs/speedtask.cpp
  jobs/transcodetask.cpp
  jobs/filtertask.cpp
  jobs/masktask.cpp
  jobs/melttask.cpp
  jobs/cachetask.cpp
  jobs/scenesplittask.cpp
  jobs/cuttask.cpp
  jobs/customjobtask.cpp
  PARENT_SCOPE)

```
