# Conversion Note: `capture/CMakeLists.txt`

## Source
- `tmp/k/src/capture/CMakeLists.txt`

## Target
- `src/Cool/capture/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Vincent PINON <vincent.pinon@laposte.net>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
#  capture/mltdevicecapture.cpp
  capture/mediacapture.cpp
  PARENT_SCOPE)



```
