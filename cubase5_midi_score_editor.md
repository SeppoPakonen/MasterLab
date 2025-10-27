# Cubase 5 — MIDI Note Editor (Score Editor) Window

> Source: detailed user walkthrough (Cubase 5). This document preserves the user‑observed UI and marks items as **Inferred**/**Unknown**/**Speculative** where appropriate.

## High‑Level Structure
- **Toolbar area** (stacked strips with tools and toggles).
- **Info Bar** directly below the top toolbar (black background, full width).
- **Main View**: notation canvas (optional **Symbols Pane** at left).  
- Opens via **MIDI → Open Score Editor** on a selected **MIDI Part** in the Project window.

---

## Top Toolbar — Part 1 (Solo & Acoustic Feedback + Four Visibility Toggles)
### Solo & Acoustic Feedback (grouped)
- **Solo Editor** — toggles solo for the edited part’s instrument channel.
- **Acoustic Feedback** — plays notes when inserting/moving them.

### Four visibility toggles
1. **Show Info Bar** — shows/hides the thin black Info Bar.
2. **Show Tool Strip** — shows/hides an additional full‑width editing tools strip.
3. **Show Filter Strip** — shows/hides a thinner filtering strip.
4. **Show Symbols Pane** — shows/hides the left pane with collapsible symbol groups (like Project Inspector).

---

## Top Toolbar — Part 2 (Primary Tools — exclusive group of 10)
Exactly **one** can be active at a time:

1. **Object Selection** (cursor)
2. **Erase** (eraser)
3. **Zoom** (magnifier) — also supports left/right click zooming.
4. **Insert Note** (note) — draw notes.
5. **Cut** (scissors)
6. **Glue** (glue stick)
7. **Show Quantize…** (opens modal)
   - **Observed form contents:**  
     - **Drop 1** (*Note Value*): **only `8`** was present.  
     - **Drop 2** (*Rests*): **only `8`** was present.  
     - **Drop 3** (*Syncopation*): `{ Relax ; Full ; (x) Off }` with **Off** shown selected.  
     - **Checkboxes:** **No Overlap**, **16 Subgroups**, **Consolidate Rests**.  
     - **Button:** **Restore to Staff** (exact effect unknown).
8. **Layout** (hand/palm + ▼) — opens a layout menu (**content not captured**).
9. **Cut Notes** (knife)
10. **Select Export Range** (dashed rectangle)

**Standalone toggle:** **Show Transpose** (vertical line with up/down arrows).

**Auto‑Scroll (Editor)** — follows playhead in this editor when transport runs.

**Velocity added to inserted note** — numeric, default **100**, range **0–127**.

**Snap** — popup with **Grid** / **Relative Grid**.

**Quantize preset** — normal grid set (`1/1 … 1/64` with dotted/triplet; **inferred** from global behavior). **Quantize Setup…** opens options.

**Length Quantize** — values `1/1 … 1/128` incl. dotted/triplet; shows a default “value/link” indicator (**label unknown**).

### Input Modes (3 independent toggles)
- **QWERTY Input** (note icon) — typing input (behavior not fully verified).  
- **Step Input** (stairs) — stepwise entry.  
- **MIDI Input** (DIN) — must be **ON** to enable the next group.

### MIDI Capture Options (requires MIDI Input = ON; 4 toggles)
1. **Thru/Insert Mode** (arrow through gate)
2. **Record Pitch**
3. **Record Velocity** (key‑on)
4. **Record Release Velocity** (key‑off)

### Hover HUD (compact 2‑line info)
- **Pitch** under mouse (e.g., `A3`)
- **Time** under mouse (`bar.beat.sixteenth.ticks`, e.g., `1.1.1.0`)

**Color** drop‑down + **Hide Colors** toggle.

---

## Info Bar (black strip; 8 logical fields when a note is selected)
1. **Start** (time)
2. **End** (time)
3. **Length** (time)
4. **Pitch** (name + octave)
5. **Velocity** (0–127)
6. **Channel** (1–16)
7. **Release Velocity** (0–127)
8. **Articulations** — shows **None**; did not open in testing. (Likely tied to **VST Expression** mapping; unknown.)

> When a **clef** is selected: three fields appear (e.g., start type/voice/position). Voice default observed as 1. (**Labels not captured**)

**Note:** Double‑clicking a note opens **Note Info** dialog (separate window).

---

## Tool Strip — Part 3 (very thin)
### Insert (4‑button group)
- Four insert buttons (icons not fully specified).

### Mystery toggle (resembles the letter “Ä”)
- On/Off; **function unknown**.

### Note Length Palette (7‑button exclusive)
- Icons from **long → short** note values.

### Augmentation modifiers (2 toggles)
- **T** = Triplet
- **Dot** = Dotted

### Enharmonic Shift
Eight **momentary** buttons (do not latch):  
`Double‑Flat (♭♭)`, `Flat (♭)`, `OFF (Auto)`, `NO`, `Sharp (♯)`, `Double‑Sharp (𝄪)`, `?`, `( )` (parentheses).

### Functions (10 buttons)
1. **Score Settings** (`i`) — dialog with **4 tabs**; bottom buttons **Help**, **Defaults**, **Apply**.  
2. **Flip** — flips stems/beams direction.  
3. **Group Notes** — beam/group selection.  
4. **Auto Layout…** — dialog with many options (improves spacing/appearance).  
5. **Hide** — hides selected objects (data retained).  
6. **Position Panel** — **no observable effect** in test. (**Unknown**)  
7. **Create Chord Symbols** — from simultaneous notes.  
8. **Force Update** (`UPD`) — refresh layout.  
9. **One Down** — **no observable effect**. (**Unknown**)  
10. **One Up** — **no observable effect**. (**Unknown**)

### Layers (all ON by default)
- **Layer 1**, **Layer 2**, **Layer 3**, **Layout Layer (L)**, **Project Layer (P)**

---

## Filter Strip — Part 4 (nine toggles)
1. **Bar Handles** (tahdinkahvat)
2. **Hidden Notes**
3. **Hide** (global)
4. **Quantize**
5. **Layout Tool**
6. **Grouping**
7. **Cutflag** — **unknown effect**.
8. **Split Rests** — **unknown behavior** in this project.
9. **Stems/Beams**

---

## Main View (Notation Canvas)
- Standard staff engraving: **Clef**, **Key Signature**, **Time Signature** (e.g., `4/4`) at left.  
- Five staff lines; barlines; ledger lines beyond range.  
- Notes draw with conventional heads/stems; direction based on midline rule.  
- Many symbols are purely **visual**; some are **functional** (clefs, key sigs, time sigs, notes, rests).  
- **Scrollbars** both directions.  
- **Zoom options:**  
  - **Small button** above the vertical scrollbar opens a menu: `{ 200% ; 150% ; 100% ; 80% ; 50% ; Hide unused }`.  
  - **Zoom Tool** also supports left/right‑click zooming.  
  - **Ctrl + Mouse Wheel** scroll‑zoom.

### Symbols Pane (left, ~50 px wide; optional)
- **11 fixed groups**, collapsible. Content does **not** depend on selection.  
  1) **Favorites** — 4×3 grid (exclusive): `staccato, tenuto, accent, fermata, pp, p, mf, f, hairpin <, slur, text, lyrics`.  
  2) **Scales** — 3×5 grid arranged by circle of fifths; center = **C major**; left **F**, right **G**; up **E♭**, down **A**.  
  3) **Clefs** — 3×2 grid:  
     - **G (Treble) — left margin** (normal size).  
     - **G (Treble) — bar‑end** (smaller, placed at **right end of the bar**).  
     - **F (Bass)**, **C (Alto/Tenor)**, **Percussion**, **TAB** (text).  
     - **TAB** is **non‑functional here**; custom tablature staff is planned separately.  
  4) **Time Signatures** — 4×2 grid: `4/4, C (common time), cut time (alla breve), 3/4, 6/4, 12/4, 6/8, 12/8`.  
  5) **VST Expression** — present but empty.  
  6) **Note Symbols** — 4×10 grid (articulations, bowings, damping, tremolos, hihat open/closed, glissandi, spoken “X”, diamond head, fermatas, DoIt, trills/ornaments, etc.).  
  7) **Dynamics** — 4×7 (+half row) with `pppp … ffff`, hairpins, sfz/sfzp/etc., arcs.  
  8) **Lines & Ornaments** — 4×7: wavy lines (up/down), L‑lines, arpeggios (plain/up/down/special), **8va/15ma**, trill lines, HS~/NS~, endings **1. / 2.**, straight/dotted/thick multi‑lines, tuplet/beam brackets (incl. “5”).  
  9) **Misc** — 4×4: Text, Lyrics, Block Text (file), Guitar TAB symbol (opens small settings), Chord Symbol (editor), Pedal (two variants), Repeat signs, Segno, Coda, Double‑Segno, **More Symbols…** (font size + large grid), Block shape, Piano keyboard outline, Image (file dialog).  
  10) **Layout** — present but disabled (all buttons inactive).  
  11) **Project** — present but disabled (all buttons inactive).

---

## Guitar Tablature (Linked Staff) — Planned Behavior
- Add a **TAB staff** below the standard staff, **time‑aligned** (shared X positions).  
- Standard **six lines** (strings). Numbers indicate **frets**: `0` = open, `1` = first fret, etc.  
- Entering a number on a TAB line inserts a **linked note** on the standard staff; note **length** editable.  
- Program auto‑inserts **rests** to the bar end under current meter.  
- **‘+’** shortens, **‘−’** lengthens the note duration.  
- **Default tuning:** **E A D G B E** (confirmed). User can change tuning; **multiple presets** available (**details to be added later**).

---

## Unknown / Speculative
- **Restore to Staff**: label confirmed; effect **unknown** (no obvious change observed).  
- **Cutflag**: present; effect **unknown** (no obvious change in this project).  
- **Position Panel**: no observable effect; purpose **unknown**.  
- **One Up / One Down**: no observable effect; possibly intended to move objects vertically or between layers — **speculative**.  
- **Articulations** in Info Bar: always “None”; likely requires VST Expression mapping; double‑clicking a note opens **Note Info** instead.

---

## Machine‑Friendly Skeleton (illustrative JSON)
```json
{
  "window": "ScoreEditor",
  "bars": {
    "top1": {
      "solo": true,
      "acousticFeedback": true,
      "toggles": ["infoBar","toolStrip","filterStrip","symbolsPane"]
    },
    "top2": {
      "exclusiveTools": ["object","erase","zoom","insertNote","cut","glue","showQuantize","layout","cutNotes","selectExportRange"],
      "standalone": ["showTranspose","autoScroll"],
      "velocityForInsert": {"default": 100, "min": 0, "max": 127},
      "snap": ["grid","relativeGrid"],
      "quantizePreset": "standard (inferred)",
      "quantizeSetupModal": {
        "noteValue": ["8"],
        "rests": ["8"],
        "syncopation": ["Relax","Full","Off*"],
        "flags": ["noOverlap","subgroups16","consolidateRests"],
        "button": "Restore to Staff"
      },
      "lengthQuantize": {"values": "1..1/128 dotted+triplet", "linkIndicator": true},
      "inputModes": {"qwerty": true, "step": true, "midi": true},
      "midiCapture": {"thruInsert": true, "pitch": true, "velocity": true, "releaseVelocity": true},
      "hoverHud": {"pitch": true, "time": true},
      "colors": {"palette": true, "hideColors": true}
    },
    "toolStripThin": {
      "insertGroup": 4,
      "mysteryToggle": true,
      "noteLengthPalette": 7,
      "modifiers": ["triplet","dotted"],
      "enharmShift": ["bb","b","auto","none","sharp","x","?","()"],
      "functions": ["scoreSettings","flip","groupNotes","autoLayout","hide","positionPanel?","createChordSymbols","forceUpdate","oneDown?","oneUp?"],
      "layers": ["1","2","3","L","P"]
    },
    "filterStrip": ["barHandles","hiddenNotes","hide","quantize","layoutTool","grouping","cutflag?","splitRests?","stems"]
  },
  "infoBar": ["start","end","length","pitch","velocity","channel","releaseVelocity","articulations(None)"],
  "symbolsPane": {
    "groups": ["favorites","scales","clefs(with TAB nonfunctional)","time","vstExpression(empty)","noteSymbols","dynamics","lines","misc","layout(disabled)","project(disabled)"]
  },
  "mainView": {
    "canvas": {
      "scrollbars": true,
      "zoomMenu": ["200%","150%","100%","80%","50%","Hide unused"],
      "zoomToolClicks": true,
      "zoomCtrlWheel": true
    },
    "tabStaff": {"lines": 6, "linkedToStaff": true, "plusMinusAdjustsLength": true, "tuning": "E A D G B E (preset-capable)"}
  }
}
```
