# Conversion Note: `xml/CMakeLists.txt`

## Source
- `tmp/k/src/xml/CMakeLists.txt`

## Target
- `src/Cool/xml/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Nicolas Carion <french.ebook.lover@gmail.com>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  xml/xml.cpp
  PARENT_SCOPE)


```
