# Conversion Note: `project/CMakeLists.txt`

## Source
- `tmp/k/src/project/CMakeLists.txt`

## Target
- `src/Cool/project/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Vincent PINON <vincent.pinon@laposte.net>

add_subdirectory(dialogs)
set(kdenlive_SRCS
  ${kdenlive_SRCS}
  project/clipstabilize.cpp
  project/cliptranscode.cpp
  project/invaliddialog.cpp
  #project/projectcommands.cpp
  project/projectmanager.cpp
  project/effectsettings.cpp
  project/notesplugin.cpp
  project/transcodeseek.cpp
  PARENT_SCOPE)

```
