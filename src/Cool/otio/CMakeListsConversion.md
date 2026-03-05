# Conversion Note: `otio/CMakeLists.txt`

## Source
- `tmp/k/src/otio/CMakeLists.txt`

## Target
- `src/Cool/otio/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-FileCopyrightText: 2024 Darby Johnston <darbyjohnston@yahoo.com>
# SPDX-License-Identifier: BSD-2-Clause

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  otio/otioexport.cpp
  otio/otioimport.cpp
  otio/otioutil.cpp
  PARENT_SCOPE
)

```
