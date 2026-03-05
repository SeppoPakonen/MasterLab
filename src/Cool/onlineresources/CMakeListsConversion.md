# Conversion Note: `onlineresources/CMakeLists.txt`

## Source
- `tmp/k/src/onlineresources/CMakeLists.txt`

## Target
- `src/Cool/onlineresources/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Julius Künzel <julius.kuenzel@kde.org>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  onlineresources/providermodel.cpp
  onlineresources/providersrepository.cpp
  onlineresources/resourcewidget.cpp
  PARENT_SCOPE)

```
