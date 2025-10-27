# Cubase 5 — Pääikkuna (Project Window)

## Elinkaari
Pääikkuna on sidottu **projektitiedostoon**; ikkunan sulkeminen sulkee projektin.

## Perusrakenne (ylhäältä alas)
1. **Työkalupalkki** (tummempi oma paletti, custom-korkeus)
2. **Infopalkki** (”Info Line”) — käänteinen värikontrasti: **musta tausta, valkoinen teksti**; kentät näyttävät labelilta ja muuttuvat edit-kentiksi fokusessa
3. **Päänäkymä** — jaettu **kolmeen pystysuikaleeseen** (noin 12% / 12% / 75%):
   - **Inspector** (vasen ~12%): valitun raidan paneelit (ryhmät kollapsoitavissa; ikonigrafiikka vaihtelee)
   - **Track List** (~12%): rivilista raidoista, työnimikentät ja peruskontrollit
   - **Project Area** (~75%): varsinainen työalue klippeineen; pysty- ja vaakascroll, zoom

> Raidat pinoutuvat vertikaalisesti; kunkin raidan korkeus on säädettävissä reunoista (kursori muuttuu vertikaalisen koonmuutoksen ikoniksi).

---

## Työkalupalkki (vasemmalta oikealle)

### Projektin tila
- **Activate Project** — virtapainikkeen näköinen toggle (aktivoi/deaktivoi projektin)
- **Constrain Delay Compensation** — toggle; aktiivisena **oranssi**

### Näkyvyys / Paneelit (5-napin ryhmä)
1. Toggle **Inspector**
2. Toggle **Info Line**
3. Toggle **minimap/overview** (pienoiskuva koko työtilasta — oletuksena piilossa)
4. Toggle **Pool**
5. Toggle **Mixer**

### Automaatio
- **Automation Panel** — avaa erikoisikkunan (ei perinteistä kehystä)
- **Automation mode** — drop-down: `Touch`, `Auto-Latch`, `Crossover`

### Transport (6-napin ryhmä)
1. **Previous Marker / To Start**
2. **Next Marker**
3. **Loop On/Off**
4. **Stop**
5. **Play**
6. **Record**

### Editointityökalut (12-napin ryhmä)
1. **Object Selection** (cursor) — avaa pienen valikon: *Normal*, *Size changes content*, *Size affects time stretch*
2. **Range Selection**
3. **Split (Scissors)**
4. **Glue**
5. **Erase**
6. **Zoom (Magnifier)**
7. **Mute (Clip Mute)**
8. **Time Warp** — valikko: *Grid*, *Grid (musical event follow)*
9. **Draw** — piirtää klippejä / automaatiota
10. **Line** — valikko: *Line*, *Parabola*, *Sine*, *Triangle*, *Square*
11. **Play Tool / Scrub**
12. **Colorize** (väri-työkalu)

- **Pitch Selector** — drop-down: (tyhjä) + **C…B** (12 säveltä)

### Scroll & Snap
- **Auto-Scroll** — toggle
- **Auto-Scroll Suspend while editing** — toggle (”puolinappi” modifier)
- **Snap On/Off** — toggle
- **Snap Type** — drop-down:
  - `Grid` (oletus)
  - `Relative Grid`
  - `Events`
  - `Shuffle`
  - `Cursor`
  - `Grid & Cursor`
  - `Events & Cursor`
  - `Events, Grid & Cursor`

### Quantize
- **Quantize Base** — drop-down: `Bar`, `Beat`, `Use Quantize`
- **Quantize Value** — drop-down: 21 vaihtoehtoa (1/1 … 1/16 + triolit & pisteelliset); alin: **Setup…** (avaa Quantize Setup -dialogin)

### Audio edit helpers
- **Snap to Zero Crossing** — toggle
- **Color Picker** — oletusväri + 16 väliväriä + **Choose Color…** (avaa värivalitsimen)

---

## Infopalkki (Info Line)

### MIDI Clip valittuna — sarakkeet
- **Name** (teksti)
- **Start**, **End**, **Length**, **Offset** (ajan formaatti = projektin näyttöformaatti; Bars+Beats oletus)
- **Mute** (On/Off)
- **Lock** (drop-down): *(tyypilliset:* empty, **Position**, **Size**, **Position+Size**, **Other**, **Position+Other**, **Size+Other** …)*
- **Transpose** (puolisävelaskelin)
- **Global Transpose** (toggle): `Follow` ↔ `Independent`
- **Velocity** (skaalaus)
- **Key** (C…B)

### Audio Clip valittuna — sarakkeet
1. **File**
2. **Description**
3. **Start**, **End**, **Length**, **Offset**
4. **Snap**
5. **Fade In**, **Fade Out**
6. **Volume (dB)**
7. **Lock**
8. **Transpose**
9. **Fine Tune**
10. **Global Transpose**
11. **Key**
12. **Mute**

> **Huomiot:**  
> - `Snap` vaikuttaa leikkeen sijaintiin ruudukkoon/kohteisiin; voi olla päällekkäinen käyttökokemus “Startin” kanssa.  
> - `Fade In/Out` oletuksena **lineaarinen**, mutta käyrää voi muokata asetuksista.  
> - `Fine Tune` tekee pieneen **taajuusalueeseen** kohdistuvan säätöpoikkeaman (pitch fine). *(inferred)*

---

## Inspector (vasen 12%)
Paneelit collapsible-otsikoilla; visuaalinen tyyli vaihtelee paneeleittain.

### Instrument Track — paneelit
1. **[Track Name]** + `E` (Edit Channel Settings)
   - **Button grid (2×6 = 12):**
     - Row 1: *Mute*, *Solo*, *Read*, *Write*, *Open Device Panels*, *Input Transformer (Off/Global/Local)*
     - Row 2: *Record Enable*, *Monitor*, *Musical/Linear Time Base*, *Lock*, *Track Lane Setup* (Off/Auto/Fixed), *Freeze Instrument*
   - **Sliders:** Volume (−∞ … +6 dB), Pan (−100 … +100; 0 default), **Track Delay** (ms, −800 … +800)
   - **Inputs:** MIDI Input (drop-down; default **All MIDI Inputs**), **Instrument Selector** (hosted VSTi)
2. **VST Expression** — drop-down kartalle (+ minikatselu aktivoituna)
3. **MIDI Inserts** — 4 paikkaa; per paikka **On** + **Effect drop-down**
4. **Equalizer** — 4 kaistaa; per kaista **On** + 3 slideria (Gain, Freq, Q) + **Type** (8 vaihtoehtoa: Parametric, High-Shelf, Low-Pass 1/2, Parametric 2, High-Shelf 2/3/4)
5. **Sends** — 8 paikkaa; per paikka **On** + **Destination drop-down** (+ mahdollinen **Bypass/Activate** -logiikka)
6. **Channel** — peilaa mikserikanavan
7. **Notepad** — tekstikenttä, tallentuu projektiin
8. **Quick Controls** — 8 kohdetta; per kohtaan **Target drop-down** + **Slider**

### Folder Track — paneelit
- **Contents** — näyttää kansion raidat; avattuna käyttäytyy kuten valitun raidan oma inspector

### FX Track — paneelit
- Ykköspaneeli: *Mute*, *Solo*, *Read*, *Write*, *Musical/Linear*, *Lock*, **Volume**, **Pan**, **Output (send-dest)**  
- **Audio Inserts** — 8 paikkaa (On, Bypass, Open UI)
- **Equalizer**, **Sends**, **Channel**, **Notepad** (kuten instrumentissa)

### Group Track — paneelit
- Sama malli kuin FX Track (ryhmäkanava)

### MIDI Track — paneelit
1. **Peruspaneeli** kuten Instrument, mutta **Instrument Selector** korvautuu **MIDI Output** -valinnalla; mukana **Drum Map** ja **Track Presets**
2. **VST Expression**
3. **MIDI Inserts**
4. **MIDI Fader** (Channel)
5. **Notepad**
6. **Quick Controls**

### Audio Track — paneelit
1. **Peruspaneeli** (ei instrumenttivalintaa; on **Audio In/Out** valinnat)
2. **Audio Inserts**
3. **Equalizer**
4. **Sends**
5. **Channel**
6. **Notepad**
7. **Quick Controls**

---

## Track List (~12% keskikaista)
Yläreunassa pieni toolbar (7 nappia):  
**[Preset Menu]**, **Edit In-Place**, **Mute All**, **Deactivate All Solos**, **Read All**, **Write All**, **Show/Hide Track Colors**.  
Oikeassa laidassa väri-nappi korostuskaistalle.

### Instrument Track (oletusnäkymä, 3 riviä)
- **Rivi 1:** Mute, Solo, *Track Name* (editoitava), Record Enable, Monitor, Read, Write
- **Rivi 2:** Edit Channel Settings, In-Place Edit, Bypass Inserts, Bypass EQ, Bypass Sends, Drum Map, Lock, Track Lanes (Off/Auto/Fixed)
- **Rivi 3:** Instrument **Preset** selector

### Audio Track (erot)
- Sama perusjoukko; tyypin väri **sininen**; toinen rivi sisältää **Musical/Linear** ja **Lock**; lisäksi **Stereo/Mono** tieto

### Kontekstivalikko (tyhjän alueen oikea klikkaus)
- **Add Audio Track**, **Add Instrument Track**, **Add MIDI Track**, **Add Arranger Track**, **Add FX Channel Track**, **Add Folder Track**, **Add Group Channel Track**, **Add Marker Track**, **Add Ruler Track**, **Add Signature Track**, **Add Tempo Track**, **Add Transpose Track**, **Add Video Track**
- **Show All Automation**, **Hide All Automation**

---

## Project Area (~75%)
- Ylin **Time Ruler** näyttää projektin ajan (oletus **Bars+Beats**).  
  - Context menu: **Bars+Beats**, **Seconds**, **Timecode**, **Samples**, **60 fps (user)**, sekä “**Linear time**” vs “**Musical (Bars+Beats) linear**” -valinnat
  - Klikkaus siirtää **transport-cursorin** kohtaan
  - Loop-alue esitetään kahdella käsikahvalla (validi = **sininen**, väärinpäin = **punainen**)

- **Ruudukko**: vaalea tausta, harmaat grid-viivat (pysty/vaaka).

- **Clipit**
  - **Audio**: näyttää yhden tai kaksi aaltoa (mono/stereo); päällä **clip name**, alareunassa **identifier**; näkyvät **fade in/out** -kahvat; sisäinen **volume-linja** (vaaka) vaikuttaa audio­käyrän piirtoon
  - **MIDI**: minimini-nuotit “pienoiskuvana” (inline)
  - **Pikatyökalupaneeli** (RMB lyhyt valikko): 12 kpl (2×6) editointityökalujen pikakuvakkeita

- **Scroll & Zoom**
  - **Oikea pysty-scroll**: yläosassa **global content zoom** (pysty); alaosassa **vertical zoom slider** (− / +)
  - **Alareunan vaaka-scroll**: oikeassa reunassa **horizontal zoom slider** (− / +)
  - Molemmilla zoom-säätimillä kontekstivalikko (presettejä: “Whole”, “~6 min”, “~1 min”, “~30 s”, “~10 s”, “~3 s”, “~1 s”; lisäksi **Manage/Organize**)
  - Pystysuuntaisessa valikossa myös: “**1 row / 2 rows / 3 rows / 4 rows**”, “**Zoom Tracks Full**”, “**Show 4 / 8 / n tracks**”, “**Lock Track Heights**”

---

## Inferred / vahvasti todennäköistä
- **Overview/minimap** on ns. *Project Overview* -paneeli. (*inferred*)
- **Automation Panel** avautuu “floating”-tyyppisenä, ilman järjestelmän otsikkopalkkia. (*inferred*)
- **Track Lane Setup** vastaa Cubase 5:n comp-lane -toimintaa. (*inferred*)

## Koneystävällinen malli (JSON Schema -tyyli, ei täysin formaali)
```json
{
  "window": "ProjectWindow",
  "areas": {
    "toolbar": { "rows": [
      {"group":"project", "items":["activateProject","constrainDelayComp"]},
      {"group":"visibility", "items":["toggleInspector","toggleInfoLine","toggleOverview","togglePool","toggleMixer"]},
      {"group":"automation", "items":["openAutomationPanel","automationMode"]},
      {"group":"transport", "items":["prevMarker","nextMarker","loop","stop","play","record"]},
      {"group":"tools", "items":["select","range","split","glue","erase","zoomTool","muteTool","timeWarp","draw","line","playTool","colorize","pitchSelector"]},
      {"group":"scrollSnap", "items":["autoScroll","autoScrollSuspend","snap","snapType"]},
      {"group":"quantize", "items":["quantizeBase","quantizeValue"]},
      {"group":"audioHelpers", "items":["snapZeroCrossing","colorPicker"]}
    ]},
    "infoLine": {"mode":"contextual", "variants":["MIDI","Audio"]},
    "leftInspector": {"type":"collapsiblePanels", "panelSets":["Instrument","Folder","FX","Group","MIDI","Audio"]},
    "trackList": {"toolbar": ["presetMenu","editInPlace","muteAll","deactivateAllSolos","readAll","writeAll","toggleTrackColors"]},
    "projectArea": {"ruler":"time", "grid":"barsBeats", "clips":["audio","midi"], "zoomControls":true}
  }
}
```
