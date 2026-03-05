# Conversion Note: `utils/CMakeLists.txt`

## Source
- `tmp/k/src/utils/CMakeLists.txt`

## Target
- `src/Cool/utils/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Jean-Baptiste Mardelle <jb@kdenlive.org>, Nicolas Carion <french.ebook.lover@gmail.com>, Julius Künzel <julius.kuenzel@kde.org>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  utils/clipboardproxy.cpp
  utils/colortools.cpp
  utils/devices.cpp
  utils/flowlayout.cpp
  utils/gentime.cpp
  utils/qcolorutils.cpp
  utils/thememanager.cpp
  utils/thumbnailcache.cpp
  utils/timecode.cpp
  utils/uiutils.cpp
  utils/qstringutils.cpp
  utils/styledspinbox.cpp
  PARENT_SCOPE
)



```
