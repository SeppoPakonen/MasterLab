# Cubase 5 — VST Connections Window

## Overview
A dedicated window fully occupied by a **tab control** with **six tabs**:
1. **Inputs**
2. **Outputs**
3. **Groups/FX**
4. **External FX**
5. **External Instruments**
6. **Studio**

Each tab follows a consistent pattern: a **toolbar** on top and a large **list/tree** below (expandable nodes), with columns matching the tab’s purpose.

> This spec conserves the exact details provided and adds a few well-founded inferences where behavior is standard for Cubase 5.

---

## Tab 1 — Inputs
**Toolbar (left → right)**  
- **Expand All (+)** and **Collapse All (−)** for the tree nodes.  
- **Add Bus…** → modal popup; choose **Channel Configuration** (`Mono`, `Stereo`, `5.0`, `5.1`, …) and **Count** (e.g., add 3 stereo busses at once).  
- **Preset** drop-down + **Save Preset** + **Delete Preset**.

**List Columns (4):**
1. **Bus Name**
2. **Speakers** (e.g., Stereo)
3. **Audio Device** (e.g., *ASIO DirectX Full Duplex*)
4. **Device Port** (per channel when expanded)

**Behavior / Example**
- Typically there is at least one defined input path. On expansion (+) a **Stereo** bus shows two child rows (**Left** and **Right**).  
- On the stereo parent row:  
  - (1) *Stereo*  
  - (2) *Stereo*  
  - (3) *ASIO DirectX Full Duplex*  
  - (4) *(empty)*  
- On the child rows: column (4) lets you bind **Device Port**: *Not Connected*, *Channel 1*, *Channel 2* (left/right assignment).

---

## Tab 2 — Outputs
Same layout as **Inputs**, plus an extra column.

**List Columns (5):**
1. **Bus Name** (expand/collapse + speaker icon; e.g., *Stereo Out*)
2. **Speakers** (e.g., Stereo)
3. **Audio Device** (click to choose: *Not Connected* or any detected ASIO device such as *ASIO DirectX Full Duplex Driver*)
4. **Device Port** (empty on the parent; selectable on child Left/Right rows)
5. **Click** (toggle text “Click” appears/disappears when you click the cell; likely routes the metronome to this bus)

**Behavior**
- Expanding the bus shows **Left** and **Right** rows.  
- On child rows, (2) and (3) are empty; column (4) picks *Not Connected* or a physical device channel.  
- Column (5) **Click** works as a simple per‑bus toggle. *(Function inferred: metronome to this output)*

---

## Tab 3 — Groups/FX
Similar overall pattern: **toolbar + list**.

**Toolbar (left → right)**  
- **Expand (+)**, **Collapse (−)**  
- **Add Group…** → modal popup (**Amount**, **Configuration**, **Speakers**)  
- **Add FX Channel…** → modal popup (**Effect** drop‑down from available FX + **Channel Configuration**; OK/Cancel)

**List Columns (3):**
1. **Bus Name** (with small type icon: group or FX)
2. **Speakers** (e.g., Stereo)
3. **Route To** (click to open context menu)

**Example Rows**
- **Group 1**:  
  - (1) “Group 1” (group icon)  
  - (2) “Stereo”  
  - (3) “Stereo Out” (menu includes: *No Bus*, *Stereo Out*, *Stereo Left*, *Stereo Right*, and any **FX channel** added)

- **FX1 CLA Drums (Mono→Stereo)**:  
  - (1) text “FX1 CLA Drums mono/stereo” (icon with bent arrow motif)  
  - (2) “Stereo”  
  - (3) “Stereo Out”

---

## Tab 4 — External FX
**Toolbar**  
- **Expand (+)**, **Collapse (−)**  
- **Add External FX…** → modal popup (**Name**, **Send Configuration**, **Return Configuration**, **Associate MIDI Device**: *No Link* / existing *MIDI Devices* / *Create MIDI Device*)  
- **Favorites** → context menu: **Add selected External FX to favorites**

**List Columns (9):**
1. **Bus Name**
2. **Speakers**
3. **Audio Device**
4. **Device Port**
5. **Delay** (ms)
6. **Send Gain** (dB)
7. **Return Gain** (dB)
8. **MIDI Device** (click to choose: *No Link*, existing MIDI devices, **Create MIDI Device**, **Open MIDI Device Manager**)
9. **Used** (boolean/marker; “currently used”)

**Behavior / Example Tree**
- Root row: **External FX** (expandable). Example root values:  
  - (1) *External FX* (+)  
  - (2) *Stereo/Stereo*  
  - (3) *(empty)*  
  - (4) *(empty)*  
  - (5) *0 ms*  
  - (6) *0 dB*  
  - (7) *0 dB*  
  - (8) *No Link* (click to choose options)  
  - (9) *(empty)*

- Child nodes under the root typically include a **Send Bus 1** and a **Return Bus 1**; expanding **Send Bus 1** shows **Left** and **Right** leaf rows.
  - **Send Bus 1**:  
    - (1) “Send Bus 1”  
    - (2) “Stereo”  
    - (3) “Not Connected” (click to pick device/driver)  
    - (4) *(empty on parent)*  
    - others empty
  - **Left / Right** (children of Send Bus 1):  
    - (4) “Not Connected” (click to bind to physical device port)
  - **Return Bus** mirrors **Send Bus** behavior.

---

## Tab 5 — External Instruments
Nearly identical to **External FX**, except the **Send Gain** column is **absent**. The toolbar action is **Add External Instrument…**.

**Add External Instrument…** modal form (OK/Cancel):  
- **Name**  
- **Number of Mono Returns**  
- **Number of Stereo Returns**  
- **Associate MIDI Device** (options: *No Link*, *MIDI Devices*, *Create MIDI Device*)

**List** mirrors External FX rows (device/ports/delay/return gain/MIDI link/used), **minus** the **Send Gain** column.

---

## Tab 6 — Studio
Visually close to **Inputs** tab but dedicated to **Control Room**.

**Toolbar**  
- Same base controls (Expand/Collapse, Presets), plus **Disable Control Room** button.  
  - Clicking **Disable Control Room** prompts a confirmation: *“Are you sure you want to disable Control Room?”* (Yes/No).

**List Example**
- Parent row: **Monitor 1** (speaker icon)  
  - (1) “Monitor 1”  
  - (2) “Stereo”  
  - (3) “Not Connected” (context menu to choose device)  
  - (4) **Device Port** (empty on parent)
- Expanding reveals **Left** and **Right** rows where **Device Port** can be assigned.

---

## Known Columns by Tab (Summary)
- **Inputs**: Bus Name | Speakers | Audio Device | Device Port  
- **Outputs**: Bus Name | Speakers | Audio Device | Device Port | **Click**  
- **Groups/FX**: Bus Name | Speakers | **Route To**  
- **External FX**: Bus Name | Speakers | Audio Device | Device Port | Delay | Send Gain | Return Gain | MIDI Device | Used  
- **External Instruments**: Bus Name | Speakers | Audio Device | Device Port | Delay | Return Gain | MIDI Device | Used *(no Send Gain)*  
- **Studio**: Bus Name | Speakers | Audio Device | Device Port

---

## Additional Notes (Inferred)
- **Click** column on **Outputs** likely toggles metronome routing to the selected output bus.  
- **Delay** column on **External FX/Instruments** is used for **round‑trip latency compensation**.  
- **Favorites** helps recall commonly patched external chains quickly.  
- **Associate MIDI Device** enables program changes/automation to external hardware.  
- **Presets** on Inputs/Outputs/Studio allow quick recall of studio I/O layouts across projects.

---

## Machine‑Friendly Model (JSON‑style, illustrative)
```json
{
  "window": "VSTConnections",
  "tabs": [
    {
      "id": "inputs",
      "toolbar": ["expandAll","collapseAll","addBus","preset","savePreset","deletePreset"],
      "columns": ["busName","speakers","audioDevice","devicePort"],
      "tree": true
    },
    {
      "id": "outputs",
      "toolbar": ["expandAll","collapseAll","addBus","preset","savePreset","deletePreset"],
      "columns": ["busName","speakers","audioDevice","devicePort","click"],
      "tree": true
    },
    {
      "id": "groupsFx",
      "toolbar": ["expandAll","collapseAll","addGroup","addFxChannel"],
      "columns": ["busName","speakers","routeTo"],
      "tree": false
    },
    {
      "id": "externalFx",
      "toolbar": ["expandAll","collapseAll","addExternalFx","favorites"],
      "columns": ["busName","speakers","audioDevice","devicePort","delayMs","sendGainDb","returnGainDb","midiDevice","used"],
      "tree": true
    },
    {
      "id": "externalInstruments",
      "toolbar": ["expandAll","collapseAll","addExternalInstrument"],
      "columns": ["busName","speakers","audioDevice","devicePort","delayMs","returnGainDb","midiDevice","used"],
      "tree": true
    },
    {
      "id": "studio",
      "toolbar": ["expandAll","collapseAll","addBus","preset","savePreset","deletePreset","disableControlRoom"],
      "columns": ["busName","speakers","audioDevice","devicePort"],
      "tree": true
    }
  ]
}
```
