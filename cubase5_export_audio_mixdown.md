# Cubase 5 — Export Audio Mixdown (Audio Mixdown -ikkuna)

## Yleiskuva
Modaalinen vienti-ikkuna, jaettu **horisontaalisella splitterillä** kahteen paneeliin:
- **Vasen paneeli** (hieman kapeampi): *Channel Batch Export* -nappi ja puunäkymä (tree control) valittaville kanaville.
- **Oikea paneeli**: varsinaiset vientiasetukset ja ohjauspainikkeet.

Ikkuna sulkeutuu *Close*-painikkeella tai aloittaa viennin *Export*-painikkeella (avaa etenemisikkunan, jossa progress bar + Cancel).

## Vasen paneeli
- **Button:** `Channel Batch Export`
- **Tree control** kanavatyypeittäin (ruksivalinnat per rivi vaikuttavat mihin tiedostoihin viedään):
  - `Output Channels`
    - esim. `Stereo Out` (tai projektin määrittelemät)
  - `Group Channels`
    - `Group 1`, `Group 2`, … (projektin ryhmäkanavat)
  - `FX Channels`
    - kaikki efektikanavat
  - `Instrument Tracks`
    - kaikki projektin instrumenttiraidat
- **Valinta-logiikka:** jokaisella rivillä checkbox; valitut rivit määräävät, mitä renderöidään erillisiksi tiedostoiksi.

## Oikea paneeli (kun vasemmalta valittuna esim. vain Stereo Out)
Ylhäältä alas:

1. **Filename** — tekstikenttä
2. **Path** — tekstikenttä (kansion polku); klikkaus avaa järjestelmän kansionvalintadialogin
3. **File Type** — *drop-down*:
   - `Wave File`
   - `AIFF File` *(kirjoitettu "if file" kuvauksessa)*
   - `MPEG1 Layer 3 File` (MP3)
   - `Ogg Vorbis File`
   - `Windows Media Audio File`
   - `Wave64 File`

4. **(Dynaaminen codec-osio)** — **näkyy File Type -valinnan ja Sample Rate -kentän välissä**. Muuttuu valinnan mukaan.
   - **Wave File** -valinnalla (WAV):
     - Checkbox: `Insert Broadcast WAV chunk`
     - Checkbox: `Don’t use WAV extensible format`
     - Checkbox: `Insert iXML chunk`
   - **MPEG1 Layer 3 File** -valinnalla (MP3):
     - Drop-down: `Bit rate`
     - Drop-down: `Sample rate`
     - Checkbox: `High quality mode`
     - Checkbox: `Insert ID3 tag`
     - Button: `Edit ID3 tag…` → **modaalinen popup** ID3-lomakkeelle (tyypillisesti kentät: Title, Artist, Album, Year, Genre, Comment — **inferred**)

5. **Sample Rate** — drop-down
6. **Bit Depth** — drop-down
7. **Export Options** — checkboxit:
   - `Mono Export`
   - `Real-Time Export`
   - `Split Channels` (stereo → L/R mono tiedostot)
   - `Update Display` (UI-päivitys viennin aikana)
8. **Post-Export options** — checkboxit:
   - `Pool` (lisää Pooliin)
   - `Audio Track` (luo raidan ja sijoita tulos projektiin)
9. **Dialog behavior** — checkbox:
   - `Close dialog after export`
10. **Actions**:
   - `Close`
   - `Export` (avaa etenemisikkunan; Progress Bar + `Cancel`)

## Etenemisikkuna (viennin jälkeen)
- **Progress Bar**
- **Button:** `Cancel`

## Inferred / vahvasti todennäköiset yksityiskohdat
- **Sample Rate** ja **Bit Depth** vaihtoehdot heijastavat projektin asetuksia (*Project Setup*), mutta voivat yliajautua viennissä — tyypillistä Cubase 5:lle.
- MP3 `Bit rate` sisältää tyypilliset CBR-arvot (esim. 128/160/192/256/320 kbps). (**inferred**)
- `Insert Broadcast WAV chunk` ja `Insert iXML chunk` lisäävät metatietoa broadcast/workstation -yhteensopivuutta varten. (**inferred**)

## Koneystävällinen malli (JSON Schema -tyyli, ei täysin formaali)
```json
{
  "window": "ExportAudioMixdown",
  "layout": {
    "split": "horizontal",
    "leftPane": {
      "widgets": [
        {"type": "button", "id": "channelBatchExport"},
        {"type": "tree", "id": "channelTree",
         "groups": ["OutputChannels","GroupChannels","FXChannels","InstrumentTracks"],
         "itemSelectable": true, "selectionType": "checkbox"}
      ]
    },
    "rightPane": {
      "widgets": [
        {"type": "text", "id": "filename"},
        {"type": "path", "id": "path", "browseDialog": true},
        {"type": "dropdown", "id": "fileType",
         "items": ["Wave","AIFF","MP3","OggVorbis","WMA","Wave64"],
         "drivesDynamicPanel": "codecPanel"},
        {"type": "panel", "id": "codecPanel", "dynamic": true},
        {"type": "dropdown", "id": "sampleRate"},
        {"type": "dropdown", "id": "bitDepth"},
        {"type": "checkboxGroup", "id": "exportOptions",
         "items": ["monoExport","realTimeExport","splitChannels","updateDisplay"]},
        {"type": "checkboxGroup", "id": "postExport",
         "items": ["addToPool","createAudioTrack"]},
        {"type": "checkbox", "id": "closeAfterExport"},
        {"type": "buttonRow", "id": "actions", "items": ["close","export"]}
      ]
    }
  },
  "dialogs": [
    {"id": "progress", "widgets": [{"type": "progressBar"}, {"type": "button", "id": "cancel"}]},
    {"id": "id3Editor", "modal": true, "when": "fileType == MP3 && insertID3",
     "widgets": [{"type": "form", "fields": ["Title","Artist","Album","Year","Genre","Comment"]}]}
  ]
}
```
