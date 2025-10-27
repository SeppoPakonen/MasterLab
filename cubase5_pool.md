# Cubase 5 — Pool (ALLAS)

## Avaaminen
**Project → Pool**. Erillinen ikkuna: **työkalupalkki**, **iso lista (tree/list hybrid)** ja **statusbar**.

## Työkalupalkki (vasemmalta oikealle)
1. **Toggle Status Bar**
2. **Play Selected**
3. **Loop (Repeat)**
4. **Volume Slider** (pysty, pieni)
5. **Column Visibility Drop-down** (näytä/piilota sarakkeita)
6. **Open All**
7. **Close All**  *(vaikuttaa puumaisen listan laajennuksiin)*
8. **Import…**
9. **Search…**
10. **Labels (oikealla, päällekkäin)**:
    - `Project Folder: <path>`
    - `Pool Record Folder: Media/Audio` *(polku suhteessa projektiin)*

## Päänäkymä: Tree/List-hybridi
- Ensimmäinen sarake näyttää puumaiset ikonit/laajennukset (+/−).
- Juurihaarat: **Audio**, **Video**, **Trash**.
- **Audio**-kansion alla tiedostot listaantuvat.
- Laajennus/tiivistys käyttäytyy kuten tiedosto­puussa.

### Sarakkeet (vasemmalta oikealle, 15 kpl)
1. **Media** (ikoni + nimi)
2. **Käytetty** (usage count)
3. **Status**
4. **Musikaalimoodi**
5. **Tempo**
6. **Signatuuri** (esim. 4/4)
7. **Avain** (juurisävel / key)
8. **Algoritmi** (esim. time-stretch -algoritmi; “MIX” tms.)
9. **Info** (esim. 44.1 kHz, 24-bit, Stereo, kesto)
10. **Tyyppi** (esim. Wave)
11. **Päivämäärä**
12. **Alkuperäinen aika projektissa** (esim. 1.01.01.000)
13. **Waveform-esikatselu**
14. **Polku** (absoluuttinen levypolku)
15. **Reel Name** (`Reel Name`)

#### Esimerkkirivi (Audio → “Amanda”)
- (1) Ikoni + **Amanda**
- (2) **1**
- (3) —
- (4) (checkbox tyhjä / ruksiton)
- (5) **120 BPM**
- (6) **4/4**
- (7) —
- (8) **MIX**
- (9) **44.1 kHz, 24-bit, Stereo, 412.06 min**
- (10) **Wave**
- (11) **10/26/2025**
- (12) **1.01.01.000**
- (13) Waveform-kuva
- (14) `C:/Users/splo/Documents/CubaseProjects/00/Audio/Amanda`
- (15) —

## Statusbar
Yksirivinen tekstilinja, esim.:  
“**1 audio file in Pool; 1 used in Project; total size 62.19 MB; external files: 0**”  
(*Huom: yksikkö todennäköisesti megatavu, ei megabitti* — **inferred**.)

## Import
**Import…** avaa järjestelmän tiedostonvalinnan. Tuettuna useita yleisiä ääniformaatteja (noin < 20 tyyppiä, dekoodattavat).

## Search
Avaa pienen **kahteen paneeliin jaetun** ikkunan.

### Vasen paneeli (”Kaavake”)
- **Drop-down (Search scope):** `Search Pool`, `[Hard Disks]`, `Select Search Path…`
- **Buttons:** `Search`, `Select`
- **Transport:** `Play`, `Stop`, `Pause`, `Repeat`
- **Volume Slider** (pieni)
- **Time position slider/field**
- **Checkbox:** `Autoplay` (alimpana)
- **Hakukenttä** (vasemmalla puolella)

### Oikea paneeli (Lista, 8 saraketta)
1. **Name**
2. **Length**
3. **Sample Rate**
4. **Bits**
5. **Channels**
6. **Date & Time**
7. **Size**
8. **Path**

## Inferred / vahvasti todennäköiset yksityiskohdat
- **Musical Mode** -sarake kytkeytyy projektin tempon seurantaan (elastinen toisto). (*inferred*)
- **Algorithm** viittaa time-stretch/pitch-shift -algoritmin esiasetukseen (esim. “Mix”, “Solo”, “Speech”). (*inferred*)
- **Reel Name** on metatietokenttä, jota käytetään kuva/post-työssä. (*inferred*)

## Koneystävällinen malli (JSON Schema -tyyli, ei täysin formaali)
```json
{
  "window": "Pool",
  "toolbar": {
    "items": ["toggleStatusBar","play","loop","volSlider","columnVisibility","openAll","closeAll","import","search"],
    "labelsRight": ["projectFolder","poolRecordFolder"]
  },
  "list": {
    "type": "treeList",
    "roots": ["Audio","Video","Trash"],
    "columns": ["media","used","status","musicalMode","tempo","signature","key","algorithm","info","type","date","originTime","wavePreview","path","reelName"]
  },
  "statusBar": {"type": "textLine"},
  "searchDialog": {
    "split": "vertical",
    "leftForm": {
      "scopeDropdown": ["Search Pool","[Hard Disks]","Select Search Path..."],
      "buttons": ["search","select"],
      "transport": ["play","stop","pause","repeat"],
      "volSlider": true, "timeSlider": true, "autoplay": true,
      "queryField": true
    },
    "rightList": {"columns": ["name","length","sampleRate","bits","channels","dateTime","size","path"]}
  }
}
```
