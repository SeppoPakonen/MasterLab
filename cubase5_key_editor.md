# Cubase 5 — MIDI Key Editor (Piano Roll / “Open Key Editor”) Window
*(Updated with verified behaviors from user testing)*

> Source: step‑by‑step observation. This spec mirrors the **actual UI/UX**; unknowns are flagged and inferences labeled.

## High-Level Concept
- The **Key Editor** follows the **last-selected MIDI part** in the Project window. Selecting non‑MIDI parts does **not** change focus; deleting the followed part **closes** the editor.
- Layout: **Toolbar** → optional **Info Bar** → **Time Ruler** → **Note Grid** (piano roll) → **Controller Lanes** (stackable).

---

## Toolbar (left → right; groups & items)

**Group A (2 toggles):** Solo Editor, Acoustic Feedback  
**Single toggle:** Show Info (toggle Info Bar)

**Group B — 10 exclusive tools (exactly one active):**
1. **Object Selection**  
2. **Draw**  
3. **Erase**  
4. **Trim**  
5. **Split**  
6. **Mute**  
7. **Glue**  
8. **Zoom** (LMB/RMB = in/out)  
9. **Line Tool** (▼): Line, Parabola, Sine, Triangle, Square, Paint  
10. **Time Warp** (▼): *Warp Grid* / *Warp Grid + Follow Musical Events* (**requires Tempo Track**)

**Group C — Auto-Scroll:**
- **Auto-Scroll** (follow playhead)
- **Suspend While Editing** (half-width; cancels follow during edits)

**Singles (x3):**
- **Auto Select Controllers** → *Observed behavior:* controller lane selection follows note selections **regardless of this toggle** (treated as **ignored** in this C5 build).  
- **Show Part Borders** (on by default)  
- **Edit Active Part Only** (E! icon)

**Parts Drop-down:** Lists MIDI parts when multiple are selected in Project.  
- **Behavior detail:** If overlapping takes are **stacked in a lane**, selecting the stack selects **all** takes → all appear in the list. If takes are **vertically separated (lanes view)**, selection can exclude takes → only selected parts appear.

**Indicate Transpositions (toggle):** When active and a **Transpose Track** affects the part, the editor **displays notes transposed** by the track’s delta (visual pitch follows the effective transpose).

**Inserted Note Velocity (0–127):** Preset menu (default **100**) + **Settings…** to edit presets.

**Snap (on/off)** and **Snap Type** (8 modes): Grid / Relative Grid / Events / Shuffle / Magnetic Cursor / Grid+Cursor / Events+Cursor / Events+Grid+Cursor.

**Quantize (grid) drop-down:** **1/1 … 1/64**, incl. **triplet** & **dotted**; **Quantize Setup…** opens the dialog.  
**Length Quantize:** **1/1 … 1/128** incl. triplet & dotted; top entry is a link-mode value.

**Input Mode (exclusive 2):** **Step Input** / **MIDI Input**.  
- **Verified:** With **Step Input** + **Virtual Keyboard** ON, each keypress inserts **one note** and advances the cursor by the **Quantize** value.

**Capture Toggles (independent 4):** Move/Insert Mode, Record Pitch, Record Velocity, Record Release Velocity.  
- First is disabled when **MIDI Input** is chosen.

**HUD #1 (2 lines):** Cursor **Pitch** (e.g., `C3`), **Time** (`bar.beat.sixteenth.ticks`, e.g., `2.3.1.0`).  
**Independent Track Loop (toggle):** Loops only this editor.  
- **Verified:** Can **coexist** with Project’s global **Cycle**. Independent loop repeats the edited part while other tracks continue past it.

**HUD #2 (2 lines):** Editor loop **Start/End** (`bar.beat…`).

**Color Mode** drop-down (+ **Settings…**): Velocity / Pitch / Channel / Part / **Grid Match** / **Sound Slot**.  
- **Grid Match (verified):** With **Snap ON**, all notes share the same color. With **Snap OFF**, color changes in **discrete 1/127 steps** by off‑grid fraction (no gradient).  
- **Sound Slot (verified):** All bars render **grey**; Program Change and CCs did **not** alter colors in tests. Mapping remains **unknown/unused** in C5.

**Live Readout:** “**Chord / Note**” analysis—updates with playback.

---

## Info Bar (when a note is selected)
1. **Start** (`bar.beat.sixteenth.ticks`)  
2. **End** (same format)  
3. **Length**  
4. **Pitch** (name + octave)  
5. **Velocity** (0–127)  
6. **Channel** (1–16; sometimes appears 0–15 as alias)  
7. **Release Velocity** (0–127)  
8. **Articulations** (from Score domain; commonly *None*)

**Scrub-to-edit:** Click value and drag **up/down** (applies to multi‑selection).

---

## Time Ruler
- Formats (context menu & right-end ▼ **identical**): **Bars+Beats**, **Seconds**, **Timecode**, **Samples**, **60 fps (user)**.  
- Optional linear modes: *Linear Time*, *Bars+Beats Linear*.  
- Graduations: taller bar ticks; shorter beat/sub ticks; beat numbers near **bottom**.  
- **Part Handles** (bottom edge) show part start/end (named) and are draggable.  
- **Loop Handles** (top edge) show editor loop; fill is violet when **Independent Track Loop** is ON.

---

## Note Grid (Main Editor Area)
**Keyboard Strip:** Vertical piano, **C notes labeled** with octave. Range **C‑2 … C9**. Black‑key rows tinted.

**Grid & Notes:**
- Edit region bounded by part start/end; outside is dimmed (horizontal guides only).  
- Notes are single‑row rectangles; length/position editable, with snap per settings.  
- Borders black, fill per color mode; label (e.g., `G1`) shown when space permits.  
- Hover → resize/move cursors; full‑width/height guides.  
- Drag tooltip: new **time** (+/−Δ), new **pitch** (+/− semitones).

**Vertical nav & zoom:** Right scrollbar + **vertical zoom slider** (− top / + bottom).

---

## Controller Lanes (“Controller Lines”)
Bottom stack of lanes for Velocity/CC/Articulations, etc.

**Lane Gutter (left):**
- **Chooser** drop‑down: *Articulations* + MIDI CCs; bottom: **Settings…**  
  - **Controllers Menu Setup (verified UI):**  
    - Two lists side‑by‑side: **“In Menu”** and **“Hidden”**  
    - Buttons **“>>>“** and **“<<<”** to move between lists  
    - **Help**, **OK**, **Cancel**
- **Readout**: shows current mouse value
- **+ / −**: add lane below / remove lane

**Display & Edit:**
- Per note-on positions, vertical filled bars (0…Max).  
- Draw/erase with Draw/Line tools; snapping per editor grid.  
- Config menu at far-left of bottom bar: **No Controller Lanes**, **Velocity Only**, **Show Used Controllers**, **Add Preset…**, **Organize…**  
  - **Add Preset…** names a preset that appears in the menu.  
  - **Organize…** dialog manages preset rename/delete.

---

## Color Modes (details)
- **Velocity:** default gradient **blue → red** (quiet → loud), configurable min/max colors.  
- **Pitch:** color by pitch-class/octave (*inferred* typical behavior).  
- **Channel:** per MIDI channel.  
- **Part:** per part when editing multiples.  
- **Grid Match:** **discrete** color change by off‑grid fraction in **1/127 steps** when **Snap OFF**; uniform when **Snap ON**.  
- **Sound Slot:** **grey only** in observed C5; mapping **unknown/unused**.

---

## Behavior Invariants
- **Snap** & **Quantize** govern both visual grid and edit constraints.  
- **Time Warp** requires a **Tempo Track**.  
- **Independent Track Loop** can run **concurrently** with Project Cycle (different regions).  
- **Part Borders** recommended ON for clear clip limits.

---

## Machine‑Readable Skeleton (illustrative JSON)
```json
{
  "window": "KeyEditor",
  "followsSelectedMidiPart": true,
  "closesWhenPartDeleted": true,
  "sections": ["toolbar","infoBar?","timeRuler","grid","controllerLanes"],
  "toolbar": {
    "soloEditor": true,
    "acousticFeedback": true,
    "showInfoBar": true,
    "toolsExclusive10": ["object","draw","erase","trim","split","mute","glue","zoom","line(line,parabola,sine,triangle,square,paint)","timeWarp(grid,grid+follow)"],
    "autoScroll": {"follow": true, "suspendWhileEditing": true},
    "autoSelectControllers": {"present": true, "effective": "ignored"},
    "showPartBorders": true,
    "editActivePartOnly": true,
    "partsDropdown": {"shows": "selected parts per selection mode (stack vs. lanes)"},
    "indicateTranspositions": {"affectsDisplayPitch": true},
    "insertVelocity": {"default": 100, "range": [0,127], "presetsEditable": true},
    "snap": {"enabled": true, "type": ["grid","relativeGrid","events","shuffle","magCursor","grid+cursor","events+cursor","events+grid+cursor"]},
    "quantize": {"values": "1/1..1/64 dotted+triplet", "setupDialog": true},
    "lengthQuantize": {"values": "1/1..1/128 dotted+triplet", "linkTopEntry": true},
    "inputMode": {"exclusive": ["step","midi"], "stepAdvancesByQuantize": true},
    "midiCapture": ["moveInsertMode","recordPitch","recordVelocity","recordReleaseVelocity"],
    "hudPitchTime": true,
    "independentTrackLoop": {"coexistsWithProjectCycle": true},
    "hudLoopRegion": true,
    "colorMode": {
      "modes": ["velocity","pitch","channel","part","gridMatch","soundSlot"],
      "gridMatch": {"snapOnUniform": true, "snapOffSteps": 127},
      "soundSlot": {"observedGreyOnly": true}
    },
    "chordNoteReadout": true
  },
  "infoBar": ["start","end","length","pitch","velocity","channel(1..16)","releaseVelocity","articulations"],
  "ruler": {"formats": ["bars+beats","seconds","timecode","samples","60fps"], "linearModes": ["time","bars+beats"], "loopHandlesTop": true, "partHandlesBottom": true, "menuButtonRightSameAsContext": true},
  "grid": {"pianoRange":"C-2..C9","blackRowsTint":true,"labelsOnC":true,"noteLabelsInsideBars":true,"guidesOnEdit":true},
  "controllerLanes": {
    "stacked": true,
    "chooser": {"hasSettingsDialog": true, "settingsUI": ["In Menu","Hidden",">>>","<<<","Help","OK","Cancel"]},
    "laneReadout": true,
    "addRemoveButtons": true,
    "lineToolSupport": true,
    "configMenu": ["none","velocityOnly","showUsed","addPreset","organize"]
  }
}
```
