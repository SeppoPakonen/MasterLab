# Conversion Note: `scopes/audioscopes/CMakeLists.txt`

## Source
- `tmp/k/src/scopes/audioscopes/CMakeLists.txt`

## Target
- `src/Cool/scopes/audioscopes/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Alberto Villa <avilla@FreeBSD.org>, Jean-Baptiste Mardelle <jb@kdenlive.org>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  scopes/audioscopes/abstractaudioscopewidget.cpp
  scopes/audioscopes/audiosignal.cpp
  scopes/audioscopes/audiospectrum.cpp
  scopes/audioscopes/spectrogram.cpp
  PARENT_SCOPE
)


```
