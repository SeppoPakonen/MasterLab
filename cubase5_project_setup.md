# Cubase 5 — Project Setup (Project Setup -ikkuna)

## Yleiskuva
Pieni **modaalinen** asetusikkuna, kompakti (suunnilleen 12×25 “pikseliyksikköä” suhteellisena kuvauksena) ja kapeahko. Sama harmaasävyinen/metallinen tyylimaailma kuin Cubase 5 yleensä. Alareunassa kolme painiketta: **Help**, **OK**, **Cancel**.

Asetukset on ryhmitelty **nimeämättömiin LabelBoxeihin** ylhäältä alas jaettuna **2 + 1 + 3 + 4**.

> **Aikaformaatit (Start, Length, Display Offset):** neliosainen kenttä (tunnit:minuutit:sekunnit:subframe), visuaalisesti “label-tyylinen” mutta muuttuu edit-kentäksi fokusoitaessa. Väriteema käänteinen (musta tausta, valkoinen teksti).

## Asetukset (10 kpl)
1. **Start** — projektin aloitushetki (ajanmuutos siirtää klippejä suhteessa uuteen alkuun; käytännössä yleensä 0:00:00:00)
2. **Length** — projektin pituus; oletus **00:10:00:00**
3. **Frame Rate (fps)** — käytetään videoraitojen kanssa (valinta mm. 24/25/29.97/30 jne.) *(inferred)*
4. **Display Format** — miten aika esitetään UI:ssa; vaihtoehdot: **Bars+Beats**, **Seconds**, **Timecode**, **Samples**, **60fps (user)**
5. **Display Offset** — visuaalinen aika-offset näyttöön (ei muuta varsinaista aikamoottorin laskentaa)
6. **Bar Offset** — tahdin offset suhteessa nollaan; esim. +1 asettaa vasemman reunan tahdiksi “-1” päänäkymässä
7. **Sample Rate** — 44.1 kHz (oletus), vaihtoehdot: 32 kHz, 48 kHz, 64 kHz, 88.2 kHz, 96 kHz
8. **Record Format (Bit Depth)** — oletus 24-bit; vaihtoehdot: 16-bit, 32-bit float
9. **Record File Type** — `Wave`, `Broadcast Wave`, `AIFF`, `Wave64` (pakkaamattomat muodot)
10. **Stereo Pan Law** — drop-down (oletus **Equal Power**): `0 dB`, `-3 dB`, `-4.5 dB`, `-6 dB`

## Painikkeet
- **Help** — avaa ohjeen
- **OK** — hyväksyy ja sulkee
- **Cancel** — peruuttaa

## Inferred / vahvasti todennäköistä
- **Frame Rate** vaikuttaa **Timecode**-näyttöön ja videorajaukseen/synkkaan. (*inferred*)
- **Display Format** vaikuttaa myös yläpalkin aikaviivaan päänäkymässä. (*inferred*)
- **Record File Type** ohjaa tulevien äänitysten oletusformaattia, ei muuta olemassa olevia tiedostoja. (*inferred*)

## Koneystävällinen malli (JSON Schema -tyyli, ei täysin formaali)
```json
{
  "window": "ProjectSetup",
  "groups": [
    {"index": 0, "contains": ["start","length"]},
    {"index": 1, "contains": ["frameRate"]},
    {"index": 2, "contains": ["displayFormat","displayOffset","barOffset"]},
    {"index": 3, "contains": ["sampleRate","recordBitDepth","recordFileType","stereoPanLaw"]}
  ],
  "fields": {
    "start": {"type": "timecode", "editableOnFocus": true},
    "length": {"type": "timecode", "default": "00:10:00:00"},
    "frameRate": {"type": "dropdown"},
    "displayFormat": {"type": "dropdown",
      "items": ["Bars+Beats","Seconds","Timecode","Samples","60fps (user)"]},
    "displayOffset": {"type": "timecode"},
    "barOffset": {"type": "integer"},
    "sampleRate": {"type": "dropdown",
      "items": ["32k","44.1k","48k","64k","88.2k","96k"]},
    "recordBitDepth": {"type": "dropdown", "items": ["16","24","32f"]},
    "recordFileType": {"type": "dropdown", "items": ["WAV","BWF","AIFF","W64"]},
    "stereoPanLaw": {"type": "dropdown",
      "items": ["EqualPower","0dB","-3dB","-4.5dB","-6dB"]}
  },
  "buttons": ["help","ok","cancel"]
}
```
