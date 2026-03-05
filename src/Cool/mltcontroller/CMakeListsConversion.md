# Conversion Note: `mltcontroller/CMakeLists.txt`

## Source
- `tmp/k/src/mltcontroller/CMakeLists.txt`

## Target
- `src/Cool/mltcontroller/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Jean-Baptiste Mardelle <jb@kdenlive.org>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
#  mltcontroller/bincontroller.cpp
#  mltcontroller/clip.cpp
  mltcontroller/clipcontroller.cpp
  mltcontroller/clippropertiescontroller.cpp
#  mltcontroller/effectscontroller.cpp
  PARENT_SCOPE)

```
