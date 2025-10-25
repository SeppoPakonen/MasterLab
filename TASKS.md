# TASKS — Development Workflow

## WAITING FOR FURTHER INFORMATION
- Implement File menu functionality
- Implement Edit menu functionality
- Implement Project menu functionality
- Implement Audio menu functionality
- Implement MIDI menu functionality
- Implement Scores menu functionality
- Implement Media menu functionality
- Implement Transport menu functionality
- Implement Devices menu functionality
- Implement Window menu functionality
- Implement Help menu functionality
- Test all package interfaces and dependencies

## TODO

23. Implement PreferencesModel with hierarchical in-memory model
24. Implement PreferencesStore with JSON/INI persistence and versioning
25. Implement PreferencePresetManager with preset CRUD and "store marked only" functionality
26. Implement PreferencesPane base class for all panels
27. Implement PrefKey<T> template for typed key bindings
28. Implement persistence schema with versioning in PreferencesStore
29. Implement TreeCtrl wiring with panel registry in PrefUI
30. Implement panel lifecycle methods (Init, Load, Store) for all preference panels
31. Create CommandIDs for Preferences/Key Commands dialogs
32. Implement runtime observers for ThemeManager, Editors, Transport, PluginManager, Scores
33. Add migration code in PreferencesStore::Migrate
34. Create .upp files for new packages with proper uses declarations
35. Create AudioOps package with files: AudioOps.h, AudioOps.cpp, OfflineOps.h, OfflineOps.cpp, Fades.h, Fades.cpp, Crossfade.h, Crossfade.cpp, Bounce.h, Bounce.cpp, Normalize.h, Normalize.cpp, Phase.h, Phase.cpp, DCOffset.h, DCOffset.cpp, Resample.h, Resample.cpp, TimeStretch.h, TimeStretch.cpp, PitchShift.h, PitchShift.cpp, Reverse.h, Reverse.cpp, Silence.h, Silence.cpp, StereoFlip.h, StereoFlip.cpp, GainOps.h, GainOps.cpp, Envelope.h, Envelope.cpp
36. Create MidiOps package with files: MidiOps.h, MidiOps.cpp, Quantize.h, Quantize.cpp, Transpose.h, Transpose.cpp, Functions.h, Functions.cpp, LogicalEditor.h, LogicalEditor.cpp, Presets.h, Presets.cpp
37. Define stable command IDs in ProjectMgmt/Commands.h
38. Implement central dispatcher in ProjectMgmt/Commands.cpp
39. Create History class with Undo/Redo functionality
40. Create Selection class for selection sets
41. Implement ProjectMgmt::Clipboard functionality
42. Implement Menu construction in AudioMaster/MainWindow.cpp binding to CommandID
43. Add required methods to AudioCore/Project.h class
44. Add required methods to AudioCore/Transport.h class
45. Add required methods to AudioCore/Mixer.h class
46. Implement ProjectMgmt::CommandManager
47. Implement ProjectMgmt::Keymap
48. Create Async job queue: FileIO::JobQueue
49. Implement preferences storage via U++ Ini/Json
50. Implement Plugin discovery cache in Devices::PluginManager
51. Create minimal UI hooks in MainWindow
52. Implement StatusBar display for mode hints and job progress
53. Create ViewFrame to host Editors, MediaPool, Browser, Score views, Mixers, Transport
54. Create .upp files for each package with proper uses declarations

## IN PROGRESS

22. Implement UI controls in PrefUI: Row, LabelBox, ColorRect, LabeledSlider, etc.

## DONE

1. Create ProjectMgmt package with files: ProjectMgmt.h, ProjectMgmt.cpp, Commands.h, Commands.cpp, History.h, History.cpp, Selection.h, Selection.cpp
2. Implement FileIO package with files: FileIO.h, FileIO.cpp, Import.h, Import.cpp, Export.h, Export.cpp, MediaFormatRegistry.h, MediaFormatRegistry.cpp, RecentFiles.h, RecentFiles.cpp, Backup.h, Backup.cpp, Templates.h, Templates.cpp
3. Create TransportUI package with files: TransportUI.h, TransportUI.cpp, Metronome.h, Metronome.cpp, CycleRange.h, CycleRange.cpp, PrePostRoll.h, PrePostRoll.cpp
4. Create Editors package with files: Editors.h, Editors.cpp, KeyEditor.h, KeyEditor.cpp, DrumEditor.h, DrumEditor.cpp, ScoreEditor.h, ScoreEditor.cpp, ListEditor.h, ListEditor.cpp, InPlaceEditor.h, InPlaceEditor.cpp
5. Create Scores package with files: Scores.h, Scores.cpp, LayoutEngine.h, LayoutEngine.cpp, NotationModel.h, NotationModel.cpp, Functions.h, Functions.cpp
6. Create MediaPool package with files: MediaPool.h, MediaPool.cpp, PoolWindow.h, PoolWindow.cpp, Conform.h, Conform.cpp, Convert.h, Convert.cpp, Search.h, Search.cpp, Integrity.h, Integrity.cpp
7. Create Browser package with files: Browser.h, Browser.cpp, MediaBay.h, MediaBay.cpp, LoopBrowser.h, LoopBrowser.cpp, SoundBrowser.h, SoundBrowser.cpp, Tagging.h, Tagging.cpp
8. Create AudioAnalysis package with files: AudioAnalysis.h, AudioAnalysis.cpp, Spectrum.h, Spectrum.cpp, Statistics.h, Statistics.cpp, Hitpoints.h, Hitpoints.cpp, Warp.h, Warp.cpp
9. Expand Preferences package with new files: PrefModel.h/.cpp, PrefStore.h/.cpp, PrefPresets.h/.cpp, PrefUI.h/.cpp, panel files (PrefAppearance.h/.cpp, PrefEditing.h/.cpp, etc.)
10. Create Theme package with files: Theme.h, Theme.cpp, WorkAreaTheme.h, WorkAreaTheme.cpp, MeterTheme.h, MeterTheme.cpp
11. Create Tooling package with files: ToolModifiers.h, ToolModifiers.cpp
12. Extend MediaPool (Media package) with MediaSettings.h/.cpp
13. Create MIDI package with files: MidiChase.h/.cpp, MidiFilterConfig.h/.cpp, MidiDisplay.h/.cpp, MidiFilePrefs.h/.cpp
14. Create AudioEditing package with files: AudioImportPrefs.h/.cpp, TimeStretchPrefs.h/.cpp, SnapSettings.h/.cpp, FadeBehavior.h/.cpp
15. Create TransportPrefs package with files: TransportPrefs.h/.cpp
16. Create VSTHost package with files: VstHostPrefs.h/.cpp
17. Create ScoresEngine package with files: ScorePrefs.h/.cpp, ScoreColors.h/.cpp, ScoreEditingPrefs.h/.cpp, NoteLayerPrefs.h/.cpp
18. Create Video package additions with VideoPrefs.h/.cpp
19. Create Appearance package with InterfaceAdjust.h/.cpp, MixerPreview.h/.cpp
20. Add new methods to AudioCore/Transport.h as specified in design
21. Add new methods to AudioCore/Project.h as specified in design
22. Implement UI controls in PrefUI: Row, LabelBox, ColorRect, LabeledSlider, etc.
23. Create Devices package with files: Devices.h, Devices.cpp, AudioDeviceManager.h, AudioDeviceManager.cpp, MidiDeviceManager.h, MidiDeviceManager.cpp, PluginManager.h, PluginManager.cpp, ReWireHost.h, ReWireHost.cpp, VideoDevice.h, VideoDevice.cpp
24. Create Windowing package with files: Windowing.h, Windowing.cpp, Workspace.h, Workspace.cpp, WindowRegistry.h, WindowRegistry.cpp
25. Create HelpAbout package with files: HelpAbout.h, HelpAbout.cpp, Credits.h, Credits.cpp, Registration.h, Registration.cpp, WebLinks.h, WebLinks.cpp
26. Create Preferences package with files: Preferences.h, Preferences.cpp, KeyCommands.h, KeyCommands.cpp, Mapping.h, Mapping.cpp
27. Create Video package with files: Video.h, Video.cpp, AudioFromVideo.h, AudioFromVideo.cpp, ReplaceAudio.h, ReplaceAudio.cpp, Thumbnail.h, Thumbnail.cpp


## IN PROGRESS

* (empty)

## DONE

* (empty)
