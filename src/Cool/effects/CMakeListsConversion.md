# Conversion Note: `effects/CMakeLists.txt`

## Source
- `tmp/k/src/effects/CMakeLists.txt`

## Target
- `src/Cool/effects/CMakeListsConversion.md`

## Phase-1 Conversion Intent
- Preserve source responsibilities and map artifact to Cool/U++ packaging notes.
- Defer compile/integration decisions to phase 2.

## Extracted Original Content
```text
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: Nicolas Carion <french.ebook.lover@gmail.com>, Jean-Baptiste Mardelle <jb@kdenlive.org>

set(kdenlive_SRCS
  ${kdenlive_SRCS}
  effects/effectbasket.cpp
  effects/effectlist/model/effectfilter.cpp
  effects/effectlist/model/effecttreemodel.cpp
  effects/effectlist/view/effectlistwidget.cpp
  effects/effectlist/view/effectlistwidget.cpp
  effects/effectsrepository.cpp
  effects/effectstack/model/abstracteffectitem.cpp
  effects/effectstack/model/effectgroupmodel.cpp
  effects/effectstack/model/effectitemmodel.cpp
  effects/effectstack/model/effectstackfilter.cpp
  effects/effectstack/model/effectstackmodel.cpp
  effects/effectstack/view/abstractcollapsiblewidget.cpp
  effects/effectstack/view/collapsibleeffectview.cpp
  effects/effectstack/view/effectstackview.cpp
  effects/effectstack/view/maskmanager.cpp
  PARENT_SCOPE)

```
