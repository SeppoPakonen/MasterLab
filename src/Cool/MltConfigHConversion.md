# Conversion Note: `mlt_config.h.in`

## Source
- `tmp/k/src/mlt_config.h.in`

## Target
- `src/Cool/MltConfigHConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
#pragma once

// define your version_libinterface
#define MLT_DATADIR "@MLT_DATADIR@"
#define MLT_MELTBIN "@MLT_MELTBIN@"

```
