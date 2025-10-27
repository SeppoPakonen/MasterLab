# Cubase 5 — Transport (Kuljetin-ikkuna)

## Yleiskuva
- **Kelluva, reunaton** ohjainikkuna (*always-on-top* käytöksellä): erittäin **matala ja leveä**.
- Näkyviin/piiloon **F2**.
- Molemmissa **yläkulmissa** on **Sulje**-nappi.
- Sisältää kuljetuspainikkeet (Play/Stop/Record/Loop/Marker-navigointi), ajanäytöt (**ensisijainen** + **toissijainen**), **progress-tyyppisen sijaintislaiderin**, **tempo- ja tahtiosion**, **punch**-ohjauksen, **synkronoinnin**, **metronomin** ja **mittarit** (MIDI & audio).  
- Oikeassa reunassa pieni **Master Output -volumeslideri** (pystysuuntaan), jonka painallus näyttää **tilapäisen ison sliderin** (~200 px korkea, ~20 px leveä) niin kauan kuin hiiren nappi on pohjassa.

> **Huom:** Kuljetin ikkunan sulkeminen ei sulje projektia (toisin kuin pääikkuna).

---

## Vasemman laidan mittarit (ASIO & Disk)
- **ASIO Time Usage** ja **Disk Preload/Cache Usage** — kaksi pystymäistä palkkia (näyttävät *latenssi-/ajankäyttökuorman* ja *levypuskurin käytön*).
- Kummankin yläpuolella **punainen Overload-led** (syttyy ylikuormassa; ASIO- tai levypuskurin **overload**).
- Nämä mittarit eivät ole audio-VU:t, vaikka muistuttavat niitä.

---

## Tallennusmoodit & Auto Quantize (3-osainen pino)
Vertikaalipino, jossa jokainen rivi on **drop-lista** tai **toggle** (ikonin + tekstin kera):

1. **Linear Record Mode** (3 vaihtoehtoa):  
   - `Normal`  
   - `Merge` (**Yhdistä**)  
   - `Replace` (**Korvaa**)
2. **Cycle Record Mode** (kun **Loop** on päällä) — 5 vaihtoehtoa:  
   - `Mix MIDI` (**mixaa midi**)  
   - `Overwrite MIDI` (**ylikirjoita midi**)  
   - `Keep Last` (**pidä viimeisin**)  
   - `Stacked 2 (no mute)` (**pinottu 2, ei mykistystä**)  
   - *(muut Cubase 5:lle tyypilliset pinotusvariantit mahdollisia — **inferred**)*
3. **Auto Quantize (MIDI)** — **toggle**; päällä ollessaan kaikki nauhoitettu **MIDI** kvantisoidaan automaattisesti.

---

## Vasemman & oikean paikantimen lohkot (Locators & Punch)
Kaksi lähes identtistä alilohkoa: **Left Locator / Punch In** ja **Right Locator / Punch Out**.

Per lohko:
- **Go to Locator** -nappi (siirtää kursoriin). **Alt + klikkaus:** aseta lokaattori nykyiseen **transport-cursorin** sijaintiin.
- **Punch**-nappi (vasemmalla *Punch In*, oikealla *Punch Out*).  
- **Ajanäyttö (Bars+Beats)** lokaattorin kohdasta.
- **Pre-Roll / Post-Roll** -kenttä (vasen lohko = **Pre-Roll**, oikea lohko = **Post-Roll**): määrittää kuinka paljon ennen/toiston jälkeen kuljetin siirtyy.

> **Inferred:** Punch toimii yhdessä **lokaattoreiden** kanssa. Pre/Post-Roll-arvot ovat **tahtimuodossa** ja vaikuttavat nauhoituksen/toiston käynnistys-/lopetusliukumiin.

---

## Keskilohko (Primary/Secondary Time, Position Slider & Transport-painikkeet)
Alue on jaettu **ylä-** ja **alapuoliskoon**.

### Yläpuolisko — aika & navigointi
- **− / +** -napit: siirrä kuljetinta aikayksikön verran vas./oik.
- **Ensisijainen ajanäyttö** (oletus: **Bars+Beats**). Vieressä **Format**-nappi (vaihtaa: **Bars+Beats**, **Seconds**, **Timecode**, **Samples**, **60 fps (user)**).
- **Swap Primary/Secondary** -nappi: vaihtaa ensisijaisen ja toissijaisen ajanäytön.  
- **Toissijainen ajanäyttö** (oletus: **Seconds**).
- **Position Slider** (alla): täyttövärillä vasen puoli kuvaa kulun.

### Alapuolisko — kahdeksan kuljetuspainiketta (vasemmalta oikealle)
1. **Previous Marker / To Start**
2. **Rewind**
3. **Fast Forward**
4. **Next Marker / To End**
5. **Cycle (Loop)**
6. **Stop**
7. **Play**
8. **Record**

---

## Metronomi, Tempo & Sync (3-osainen pino)
Vertikaalisesti kolme erikorkuista osaa:

1. **Metronomi**
   - **Click On/Off** -nappi. **Ctrl + klikkaus:** avaa **Metronome Setup**.
   - Pieni **Precount**-nappi (esilaskenta; esim. 1 tahti ennen toistoa/nauhoitusta).

2. **Tempo & Signature** (hieman korkeampi lohko)
   - **Fixed Tempo / Tempo Track** -vaihto (toggle).
   - **Signature**-edit (esim. 4/4).
   - **Tempo Value** -näyttö (päivittyy tempo-raitaa seuraten, jos **Tempo Track** aktiivinen).

3. **Sync**
   - **External Sync** -toggle (ottaa ulkoisen synkan käyttöön).  
   - **Ctrl + klikkaus:** avaa **Synchronization Settings** (vaihtoehdot tyypillisesti: **Internal**, **MIDI Time Code (MTC)**, **VST System Link**, **ASIO** jne. — **inferred**).

---

## Marker-pikaohjaus
Noin nelijakoinen alue, jossa:
- **Show Markers** -nappi (avaa markerilistauksen).
- **Pikapainikkeet** markkereille:  
  - rivi 2: **1–5**  
  - rivi 3: **6–10**  
  - rivi 4: **11–15**  
- **Alt + klikkaus** markerin numerossa **siirtää** kyseisen markerin **nykyiseen kursoriin**.

---

## MIDI- & Audio-aktiivisuusmittarit
- **MIDI In / MIDI Out**: kaksi kapeaa pystypalkkia (aktiivisuus).
- **Audio In / Audio Out**: neljä pystypalkkia (stereoprojekti = 2×2; useammille kanaville omat palkit).  
  - Palkkien yläreunassa **Clip-ledit**, jotka **latchaavat** (pysyvät punaisina kunnes käyttäjä kuittaa klikkaamalla).

---

## Master Output -volume (oikea reuna)
- **Kapea pystyslideri** (< 10 px). Klikkaus ja pitäminen auki näyttää **tilapäisen ison sliderin** (~200 px korkea). Vapauttaessa palaa piiloon.

---

## Virtuaalinen koskettimisto (Alt + K)
Kuljetinikkuna levenee ja avaa **Virtual Keyboard** -tilan.

### Tila A — *QWERTY-bindaukset* (oletus, 1 oktaavi)
- Valkoiset koskettimet: **Q – I** (Q, W, E, R, T, Y, U, I).  
- Mustat koskettimet: **2, 3, 5, 6, 7**.
- Koskettimissa **näkyy** näppäinsidonnan teksti; painaminen **täyttää** näppäimen värillä.
- Alapuolella **matalat oktaavipainikkeet** (n. 7 kpl) oktaavin vaihtoon.

### Tila B — *Pianografiikka* (SHIFT + TAB)
- Näkyviin **3 oktaavin** leveä pianon kuva **ilman** näppäinmerkintöjä.
- Alareunassa **oktaavivalitsin**, jota voi **raahata** vas./oik. säätääksesi näkyvää aluetta.
- Vasemmalla **kaksi slideriä** (modulaatiorullat).  
- Oikealla **pystysuuntainen Velocity-slider** (nuotin voimakkuus).
- **SHIFT + TAB** uudelleen palaa **Tila A:han**.

---

## Inferred / vahvasti todennäköistä
- **Punch In/Out** kytkeytyy **Left/Right Locator** -asemiin; Cycle-toisto käyttää samoja lokaatteja.  
- **Position Slider** toimii myös **scrubbina** pienin liikkein.  
- **External Sync** ohittaa projektin sisäisen tempon/ajan, ja **tempoarvo** on tällöin vain näyttöä.  
- **Metronomin Precount** vaikuttaa sekä **Play**- että **Record**-käynnistyksiin.  

---

## Koneystävällinen malli (JSON-tyylinen, ei täysin formaali)
```json
{
  "window": "Transport",
  "isFloating": true,
  "alwaysOnTop": true,
  "controls": {
    "closeButtons": ["topLeft","topRight"],
    "meters": {
      "asioUsage": {"type":"bar","overloadLed":true},
      "diskUsage": {"type":"bar","overloadLed":true}
    },
    "recording": {
      "linearMode": ["Normal","Merge","Replace"],
      "cycleMode": ["MixMIDI","OverwriteMIDI","KeepLast","Stacked2NoMute"],
      "autoQuantize": {"type":"toggle","target":"MIDI"}
    },
    "locators": {
      "left": {"time":"barsBeats","preRoll":"barsBeats","goTo":true,"punchIn":true,"altClickSetHere":true},
      "right": {"time":"barsBeats","postRoll":"barsBeats","goTo":true,"punchOut":true,"altClickSetHere":true}
    },
    "timeArea": {
      "nudge": {"minus":true,"plus":true},
      "primaryTime": {"formats":["BarsBeats","Seconds","Timecode","Samples","60fpsUser"],"swapWithSecondary":true},
      "secondaryTime": {},
      "positionSlider": {"type":"progress","scrubLike": true}
    },
    "transportButtons": ["prevMarkerOrStart","rewind","fastForward","nextMarkerOrEnd","cycle","stop","play","record"],
    "metronome": {"click":true,"precount":true,"ctrlOpensSetup":true},
    "tempo": {"useFixed":true,"useTempoTrack":true,"signature":true,"tempoValue":true},
    "sync": {"external":true,"ctrlOpensSyncSettings":true},
    "markers": {
      "openList": true,
      "quickJump": {"1-5": true,"6-10": true,"11-15": true},
      "altClickReassign": true
    },
    "activity": {
      "midi": ["in","out"],
      "audio": {"channels": "stereoOrMore", "clipLeds": "latching"}
    },
    "masterVolume": {"type":"verticalSlider","compact":true,"pressShowsLarge":true}
  },
  "virtualKeyboard": {
    "toggle": "Alt+K",
    "modeA": {"keysWhite":"Q..I","keysBlack":[2,3,5,6,7],"octaveButtons":7,"labeled":true},
    "modeB": {"octavesVisible":3,"modWheels":2,"velocitySlider":true,"draggableOctaveRange":true,"switch":"Shift+Tab"}
  }
}
```
