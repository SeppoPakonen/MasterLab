# Conversion Note: `audiomixer/audiolevels/CMakeLists.txt`

## Source
- `tmp/k/src/audiomixer/audiolevels/CMakeLists.txt`

## Target
- `src/Cool/audiomixer/audiolevels/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Jean-Baptiste Mardelle <jb@kdenlive.org>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  audiomixer/audiolevels/audiolevelwidget.cpp
  audiomixer/audiolevels/audiolevelconfig.cpp
  audiomixer/audiolevels/audiolevelstyleprovider.cpp
  audiomixer/audiolevels/audiolevelrenderer.cpp
PARENT_SCOPE)

```
