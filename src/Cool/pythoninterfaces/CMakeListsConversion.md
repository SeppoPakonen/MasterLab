# Conversion Note: `pythoninterfaces/CMakeLists.txt`

## Source
- `tmp/k/src/pythoninterfaces/CMakeLists.txt`

## Target
- `src/Cool/pythoninterfaces/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Julius Künzel <julius.kuenzel@kde.org>

add_subdirectory(dialogs)
set(kdenlive_SRCS
  ${kdenlive_SRCS}
  pythoninterfaces/saminterface.cpp
  pythoninterfaces/speechtotext.cpp
  pythoninterfaces/speechtotextvosk.cpp
  pythoninterfaces/speechtotextwhisper.cpp
  pythoninterfaces/abstractpythoninterface.cpp
  PARENT_SCOPE
)

```
