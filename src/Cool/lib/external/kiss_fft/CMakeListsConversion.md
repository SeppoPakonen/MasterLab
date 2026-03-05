# Conversion Note: `lib/external/kiss_fft/CMakeLists.txt`

## Source
- `tmp/k/src/lib/external/kiss_fft/CMakeLists.txt`

## Target
- `src/Cool/lib/external/kiss_fft/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-FileCopyrightText: 2012 Simon A. Eugster (Granjow) <simon.eu@gmail.com>
# SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL

# Create a static library from kiss_fft
include_directories(${CMAKE_BINARY_DIR})
add_library(kiss_fft STATIC _kiss_fft_guts.h kiss_fft.c kiss_fftr.c)

```
