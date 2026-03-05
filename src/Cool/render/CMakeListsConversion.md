# Conversion Note: `render/CMakeLists.txt`

## Source
- `tmp/k/src/render/CMakeLists.txt`

## Target
- `src/Cool/render/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Julius Künzel <julius.kuenzel@kde.org>

#if(NOT USE_DBUS)
    list(APPEND kdenlive_SRCS
      render/renderserver.cpp)
#endif()

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  render/renderrequest.cpp
  PARENT_SCOPE)

```
