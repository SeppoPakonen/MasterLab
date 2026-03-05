# Conversion Note: `pythoninterfaces/dialogs/CMakeLists.txt`

## Source
- `tmp/k/src/pythoninterfaces/dialogs/CMakeLists.txt`

## Target
- `src/Cool/pythoninterfaces/dialogs/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Vincent PINON <vincent.pinon@laposte.net>, Jean-Baptiste Mardelle <jb@kdenlive.org>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  pythoninterfaces/dialogs/whisperdownload.cpp
  pythoninterfaces/dialogs/modeldownloadwidget.cpp
  PARENT_SCOPE)


```
