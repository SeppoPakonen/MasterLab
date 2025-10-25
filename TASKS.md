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

9. Create AudioOps package with files: AudioOps.h, AudioOps.cpp, OfflineOps.h, OfflineOps.cpp, Fades.h, Fades.cpp, Crossfade.h, Crossfade.cpp, Bounce.h, Bounce.cpp, Normalize.h, Normalize.cpp, Phase.h, Phase.cpp, DCOffset.h, DCOffset.cpp, Resample.h, Resample.cpp, TimeStretch.h, TimeStretch.cpp, PitchShift.h, PitchShift.cpp, Reverse.h, Reverse.cpp, Silence.h, Silence.cpp, StereoFlip.h, StereoFlip.cpp, GainOps.h, GainOps.cpp, Envelope.h, Envelope.cpp
10. Create MidiOps package with files: MidiOps.h, MidiOps.cpp, Quantize.h, Quantize.cpp, Transpose.h, Transpose.cpp, Functions.h, Functions.cpp, LogicalEditor.h, LogicalEditor.cpp, Presets.h, Presets.cpp
16. Define stable command IDs in ProjectMgmt/Commands.h
17. Implement central dispatcher in ProjectMgmt/Commands.cpp
18. Create History class with Undo/Redo functionality
19. Create Selection class for selection sets
20. Implement ProjectMgmt::Clipboard functionality
21. Implement Menu construction in AudioMaster/MainWindow.cpp binding to CommandID
22. Add required methods to AudioCore/Project.h class
23. Add required methods to AudioCore/Transport.h class
24. Add required methods to AudioCore/Mixer.h class
25. Implement ProjectMgmt::CommandManager
26. Implement ProjectMgmt::Keymap
27. Create Async job queue: FileIO::JobQueue
28. Implement preferences storage via U++ Ini/Json
29. Implement Plugin discovery cache in Devices::PluginManager
30. Create minimal UI hooks in MainWindow
31. Implement StatusBar display for mode hints and job progress
32. Create ViewFrame to host Editors, MediaPool, Browser, Score views, Mixers, Transport
33. Create .upp files for each package with proper uses declarations

## DONE

1. Create ProjectMgmt package with files: ProjectMgmt.h, ProjectMgmt.cpp, Commands.h, Commands.cpp, History.h, History.cpp, Selection.h, Selection.cpp
2. Implement FileIO package with files: FileIO.h, FileIO.cpp, Import.h, Import.cpp, Export.h, Export.cpp, MediaFormatRegistry.h, MediaFormatRegistry.cpp, RecentFiles.h, RecentFiles.cpp, Backup.h, Backup.cpp, Templates.h, Templates.cpp
3. Create TransportUI package with files: TransportUI.h, TransportUI.cpp, Metronome.h, Metronome.cpp, CycleRange.h, CycleRange.cpp, PrePostRoll.h, PrePostRoll.cpp
4. Create Editors package with files: Editors.h, Editors.cpp, KeyEditor.h, KeyEditor.cpp, DrumEditor.h, DrumEditor.cpp, ScoreEditor.h, ScoreEditor.cpp, ListEditor.h, ListEditor.cpp, InPlaceEditor.h, InPlaceEditor.cpp
5. Create Scores package with files: Scores.h, Scores.cpp, LayoutEngine.h, LayoutEngine.cpp, NotationModel.h, NotationModel.cpp, Functions.h, Functions.cpp
6. Create MediaPool package with files: MediaPool.h, MediaPool.cpp, PoolWindow.h, PoolWindow.cpp, Conform.h, Conform.cpp, Convert.h, Convert.cpp, Search.h, Search.cpp, Integrity.h, Integrity.cpp
7. Create Browser package with files: Browser.h, Browser.cpp, MediaBay.h, MediaBay.cpp, LoopBrowser.h, LoopBrowser.cpp, SoundBrowser.h, SoundBrowser.cpp, Tagging.h, Tagging.cpp
8. Create AudioAnalysis package with files: AudioAnalysis.h, AudioAnalysis.cpp, Spectrum.h, Spectrum.cpp, Statistics.h, Statistics.cpp, Hitpoints.h, Hitpoints.cpp, Warp.h, Warp.cpp
11. Create Devices package with files: Devices.h, Devices.cpp, AudioDeviceManager.h, AudioDeviceManager.cpp, MidiDeviceManager.h, MidiDeviceManager.cpp, PluginManager.h, PluginManager.cpp, ReWireHost.h, ReWireHost.cpp, VideoDevice.h, VideoDevice.cpp
12. Create Windowing package with files: Windowing.h, Windowing.cpp, Workspace.h, Workspace.cpp, WindowRegistry.h, WindowRegistry.cpp
13. Create HelpAbout package with files: HelpAbout.h, HelpAbout.cpp, Credits.h, Credits.cpp, Registration.h, Registration.cpp, WebLinks.h, WebLinks.cpp
14. Create Preferences package with files: Preferences.h, Preferences.cpp, KeyCommands.h, KeyCommands.cpp, Mapping.h, Mapping.cpp
15. Create Video package with files: Video.h, Video.cpp, AudioFromVideo.h, AudioFromVideo.cpp, ReplaceAudio.h, ReplaceAudio.cpp, Thumbnail.h, Thumbnail.cpp


## IN PROGRESS

* (empty)

## DONE

* (empty)
