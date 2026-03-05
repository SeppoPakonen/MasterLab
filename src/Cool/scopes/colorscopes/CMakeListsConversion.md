# Conversion Note: `scopes/colorscopes/CMakeLists.txt`

## Source
- `tmp/k/src/scopes/colorscopes/CMakeLists.txt`

## Target
- `src/Cool/scopes/colorscopes/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Alberto Villa <avilla@FreeBSD.org>, Jean-Baptiste Mardelle <jb@kdenlive.org>, Vincent PINON <vincent.pinon@laposte.net>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  scopes/colorscopes/colorconstants.h
  scopes/colorscopes/abstractgfxscopewidget.cpp
  scopes/colorscopes/colorplaneexport.cpp
  scopes/colorscopes/histogram.cpp
  scopes/colorscopes/histogramgenerator.cpp
  scopes/colorscopes/rgbparade.cpp
  scopes/colorscopes/rgbparadegenerator.cpp
  scopes/colorscopes/vectorscope.cpp
  scopes/colorscopes/vectorscopegenerator.cpp
  scopes/colorscopes/waveform.cpp
  scopes/colorscopes/waveformgenerator.cpp
  PARENT_SCOPE
)

```
