# Conversion Note: `lib/audio/CMakeLists.txt`

## Source
- `tmp/k/src/lib/audio/CMakeLists.txt`

## Target
- `src/Cool/lib/audio/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-FileCopyrightText: 2012 Simon A. Eugster (Granjow) <simon.eu@gmail.com>
# SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL

set(kdenlive_SRCS
    ${kdenlive_SRCS}
    lib/audio/audioCorrelation.cpp
    lib/audio/audioCorrelationInfo.cpp
    lib/audio/audioEnvelope.cpp
    lib/audio/audioInfo.cpp
    lib/audio/audioStreamInfo.cpp
    lib/audio/fftCorrelation.cpp
    lib/audio/fftTools.cpp
    PARENT_SCOPE
)

```
