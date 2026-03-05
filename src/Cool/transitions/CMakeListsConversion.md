# Conversion Note: `transitions/CMakeLists.txt`

## Source
- `tmp/k/src/transitions/CMakeLists.txt`

## Target
- `src/Cool/transitions/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Nicolas Carion <french.ebook.lover@gmail.com>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  transitions/transitionsrepository.cpp
  transitions/transitionlist/view/transitionlistwidget.cpp
  transitions/transitionlist/model/transitiontreemodel.cpp
  transitions/transitionlist/model/transitionfilter.cpp
  transitions/view/transitionstackview.cpp
  transitions/view/mixstackview.cpp
  PARENT_SCOPE)


```
