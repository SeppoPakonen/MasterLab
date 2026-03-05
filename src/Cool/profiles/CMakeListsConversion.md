# Conversion Note: `profiles/CMakeLists.txt`

## Source
- `tmp/k/src/profiles/CMakeLists.txt`

## Target
- `src/Cool/profiles/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Nicolas Carion <french.ebook.lover@gmail.com>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  profiles/profileinfo.cpp
  profiles/profilerepository.cpp
  profiles/profilemodel.cpp
  profiles/tree/profiletreemodel.cpp
  profiles/tree/profilefilter.cpp
  PARENT_SCOPE)


```
