# Conversion Note: `project/dialogs/CMakeLists.txt`

## Source
- `tmp/k/src/project/dialogs/CMakeLists.txt`

## Target
- `src/Cool/project/dialogs/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Vincent PINON <vincent.pinon@laposte.net>, Jean-Baptiste Mardelle <jb@kdenlive.org>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  project/dialogs/archivewidget.cpp
  project/dialogs/backupwidget.cpp
  project/dialogs/noteswidget.cpp
  project/dialogs/projectsettings.cpp
  project/dialogs/slideshowclip.cpp
  project/dialogs/temporarydata.cpp
  project/dialogs/profilewidget.cpp
  project/dialogs/guidecategories.cpp
  project/dialogs/guideslist.cpp
  PARENT_SCOPE)


```
