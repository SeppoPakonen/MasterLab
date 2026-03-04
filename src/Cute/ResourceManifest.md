# Legacy `qtractor.qrc` Conversion Notes

## Source
- Original file: `tmp/q/src/qtractor.qrc`
- Phase: Cute phase 1
- Intent: preserve the original Qt resource inventory so phase 2 can map it onto U++ image/layout asset loading.

## Inventory Summary
- Total resource entries: `140`
- Resource prefix in the Qt file: `/`
- All listed assets come from `tmp/q/src/images/`

## Main Groups
- Application identity icons:
  - `qtractor.png`, `qtractor.svg`
  - `qtractorConnections.*`, `qtractorMidiEditor.*`, `qtractorMixer.*`, `qtractorPlugin.*`, `qtractorTracks.png`
- Clip/edit toolbar icons:
  - `clipEdit.png`, `clipNew.png`, `clipRecord.png`
  - `editCopy.png`, `editCut.png`, `editDelete.png`, `editPaste.png`, `editRedo.png`, `editUndo.png`
  - `editModeDraw.png`, `editModeOff.png`, `editModeOn.png`
  - `editSelectClip.png`, `editSelectRange.png`, `editSelectRect.png`, `editSelectCurve.png`
  - `fadeIn.png`, `fadeOut.png`
- File/form action icons:
  - `fileNew.png`, `fileOpen.png`, `fileSave.png`
  - `formAccept.png`, `formAdd.png`, `formColor.png`, `formConnect.png`, `formCreate.png`
  - `formDisconnect.png`, `formDisconnectAll.png`, `formEdit.png`, `formMoveDown.png`, `formMoveUp.png`
  - `formOpen.png`, `formRefresh.png`, `formReject.png`, `formRemove.png`, `formSave.png`
- Browser/item icons:
  - audio and MIDI client/port/file icons
  - channel, group, instrument, note/controller/property icons
  - LED state icons and session file icon
- Plugin and track icons:
  - `pluginEdit.png`, `pluginProperties.png`, `pluginSelect.png`
  - `trackAdd.png`, `trackAudio.png`, `trackMidi*.png`, `trackProperties.png`, `trackRemove.png`
  - track curve state icons and instrument pictograms (`Bass`, `Drums`, `Guitar`, `Microphone`, `Piano`, `Speaker`, `Trumpet`, `Violin`)
- Transport icons:
  - play/stop/record/rewind/fast-forward family
  - loop, metronome, punch, panic, follow, count-in, transport mode icons
- View icons:
  - connections, drum mode, events, files, file system, messages, mixer, preview, zoom controls

## U++ Direction
The Qt `.qrc` resource file should not be copied directly.

Phase-2 options:
- keep image files on disk and load them through U++ `Image` / `StreamRaster` helpers at runtime
- generate a U++ image set package if repeated toolbar usage makes that worthwhile
- embed selected assets through a `.brc` file, following the pattern used in `../ai-upp/reference/brc/bin.cpp` and `../ai-upp/reference/brc/bin.brc`
- split ownership by package so icons stay near the code that uses them

## Suggested Package Ownership
- `AudioMaster`: application identity icons and high-level window/view icons
- `AudioEditing`: clip/edit toolbar icons and fade/edit-mode icons
- `VSTConnections`: connection and routing icons
- `MIDI`: MIDI editor and controller-related icons
- `ProjectWindow`: track and arranger icons
- `TransportUI`: transport state icons
- `Theme`: shared form action icons and common UI imagery

## Phase 2 Work Needed
- decide whether the Cute build keeps raw image files in the runtime data directory, converts them into a U++ image package, or embeds subsets with `.brc`
- create a lookup layer so converted code does not hardcode Qt resource paths like `:images/...`
- update toolbar/menu/dialog conversions to use the new lookup layer

## Manifest Notes For Later
- `script/build.py Cute` should package the required image assets beside the executable or in the final data tree
- if a U++ image package is introduced, its `.upp` should stay separate from `Cute` and be reused by the package that owns the icons
