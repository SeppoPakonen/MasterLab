# TASKS — Development Workflow

## PHASE 1: CORE FOUNDATION (Months 1-3)
*Milestone: Basic Project Management*

### Resource Allocation
- 2 full-time developers for core architecture
- 1 part-time UI designer for basic interface elements

### Completion Criteria
- ProjectMgmt package has full command system architecture
- Basic project operations are functional
- AudioCore has basic track and event model
- All core packages have proper header and implementation files

### Immediate Priorities
1. Expand ProjectMgmt with full command system architecture
2. Implement CommandManager with registry and dispatch functionality
3. Create Command base class and specific command implementations
4. Implement Undo/Redo stack with History class
5. Implement FileIO package with basic project operations
6. Extend AudioCore with basic track and event model

### Secondary Priorities
7. Define stable command IDs for all functions in WINDOW_KEY_COMMANDS.md
8. Create CommandContext for execution context management
9. Implement basic menu system binding to CommandIDs
10. Add required methods to AudioCore/Mixer.h class

## PHASE 2: BASIC EDITING INFRASTRUCTURE (Months 4-6)
*Milestone: Functional Audio/MIDI Editing*

### Resource Allocation
- 2 full-time developers for editor implementation
- 1 full-time developer for audio/MIDI processing
- 1 part-time UI designer for interface elements

### Completion Criteria
- Core editor types (Key, List) are fully functional
- Basic Audio/MIDI processing capabilities are operational
- Transport system has basic play, stop, record functionality
- UI has basic menu system and view management

### Primary Tasks
11. Complete Editors package with core editor types (Key, List)
12. Establish MidiInsert processing framework in PluginSDK and register stub packages
13. Implement Arpache5/ArpacheSX arpeggiators with shared chord tracking and order resolver modules
14. Implement Chorder, ContextGate, and MicroTuner using shared harmony/tuning services
15. Implement BeatDesigner, StepDesigner, and AutoLFO pattern engines with common pattern storage
16. Implement core MIDI processing inserts (MidiCompressor, Density, MidiModifiers, MidiEcho, NoteToCC)
17. Implement controller/utility inserts (MidiController, TrackControl, MidiMonitor, Quantizer, Transformer)
18. Implement basic AudioOps processing capabilities
19. Implement basic MidiOps processing capabilities
20. Build basic transport system in TransportUI
21. Create basic editing tools in Editors/Tools

### Supporting Tasks
22. Implement complete menu system binding to CommandIDs
23. Create ViewFrame to host all editor views
24. Implement StatusBar display for mode hints and job progress
25. Create minimal UI hooks in MainWindow
26. Implement ProjectMgmt::CommandManager

## PHASE 3: ADVANCED EDITING FEATURES (Months 7-9)
*Milestone: Professional Editing Capabilities*

### Resource Allocation
- 2 full-time developers for advanced editor implementation
- 1 full-time developer for automation system
- 1 part-time UI designer for advanced interface elements

### Completion Criteria
- All editor types (Drum, Score, InPlace) are fully functional
- Advanced Audio/MIDI processing capabilities are operational
- Automation system is fully integrated
- Selection system supports multi-item operations

### Primary Tasks
27. Complete Editors package with all editor types (Drum, Score, InPlace)
28. Implement advanced AudioOps processing capabilities
29. Implement advanced MidiOps processing capabilities
30. Build advanced editing tools in Editors/Tools
31. Extend AudioCore with advanced track hierarchy

### Supporting Tasks
32. Implement Event system with audio, MIDI, automation support
33. Create TrackParameter and automation systems
34. Implement advanced track types (folder, group, FX, instrument)
35. Build Selection system for multi-item operations

## PHASE 4: PLUGIN ARCHITECTURE (Months 10-12)
*Milestone: Plugin Hosting and Integration*

### Resource Allocation
- 2 full-time developers for plugin system architecture
- 1 full-time developer for plugin integration
- 1 part-time specialist for plugin API compatibility

### Completion Criteria
- Complete plugin hosting system is operational
- Plugin discovery, loading, and management are functional
- VST/AU/AAX plugin wrappers work with the system
- Async job queue handles background operations

### Primary Tasks
36. Extend Devices package with complete plugin hosting system
37. Implement PluginManager with discovery and loading capabilities
38. Create VST/AU/AAX plugin wrappers
39. Implement plugin parameter and preset management
40. Create plugin GUI integration system

### Supporting Tasks
41. Implement Plugin discovery cache in Devices::PluginManager
42. Add required methods to AudioCore/Mixer.h class
43. Implement runtime observers for ThemeManager, Editors, Transport, PluginManager, Scores
44. Create Async job queue: FileIO::JobQueue

## PHASE 5: SCRIPTING AND AUTOMATION (Months 13-15)
*Milestone: Scripting Engine and Advanced Automation*

### Resource Allocation
- 2 full-time developers for scripting engine
- 1 full-time developer for automation systems
- 1 part-time developer for macro recording features

### Completion Criteria
- Scripting engine is fully operational with execution environment
- Macro recording and playback functionality works
- Preset management system is integrated
- Preferences storage system is fully implemented

### Primary Tasks
45. Create Scripts package for logical processing
46. Implement ScriptEngine with execution environment
47. Create LogicalProcessor for script evaluation
48. Implement PresetManager for process presets
49. Create MacroRecorder for user-defined command sequences

### Supporting Tasks
50. Implement preferences storage via U++ Ini/Json
51. Add migration code in PreferencesStore::Migrate
52. Implement ProjectMgmt::Clipboard functionality
53. Implement ProjectMgmt::Keymap

## PHASE 6: PROFESSIONAL FEATURES (Months 16-18)
*Milestone: Professional Production Environment*

### Resource Allocation
- 2 full-time developers for media management and views
- 1 full-time developer for windowing system
- 1 full-time technical writer for documentation

### Completion Criteria
- Media pool has advanced media management capabilities
- Views system supports different display modes
- Windowing system manages workspaces effectively
- Help and documentation system is accessible

### Primary Tasks
54. Complete MediaPool package with advanced media management
55. Implement Views system for different display modes
56. Create Windowing package with workspace management
57. Build HelpAbout package with documentation and support

### Supporting Tasks
58. Implement PreferencePresetManager with preset CRUD and "store marked only" functionality
59. Implement PreferencesPane base class for all panels
60. Implement PrefKey<T> template for typed key bindings
61. Implement persistence schema with versioning in PreferencesStore

## PHASE 7: OPTIMIZATION AND POLISH (Months 19-21)
*Milestone: Performance Optimization and Quality Assurance*

### Resource Allocation
- 2 full-time developers for optimization
- 1 full-time QA engineer for testing framework
- 1 part-time technical writer for documentation

### Completion Criteria
- Real-time audio processing meets performance requirements
- Comprehensive testing framework is operational
- Cross-platform compatibility is verified
- Documentation and tutorials are complete

### Primary Tasks
62. Optimize real-time audio processing performance
63. Implement comprehensive testing framework
64. Fix bugs and improve stability
65. Enhance cross-platform compatibility

### Supporting Tasks
66. Complete documentation and tutorial content
67. Implement performance monitoring and diagnostics
68. Create professional marketing materials
69. Set up customer support infrastructure

## PHASE 8: MARKET RELEASE (Month 22)
*Milestone: Commercial Release*

### Resource Allocation
- 1 full-time developer for installer and distribution
- 1 full-time developer for licensing system
- 1 full-time marketing specialist for campaign launch

### Completion Criteria
- Installer and distribution system are operational
- Licensing and registration system works properly
- Update mechanism is set up and functional
- Marketing campaign is launched successfully

### Primary Tasks
70. Create installer and distribution system
71. Implement licensing and registration system
72. Set up update mechanism
73. Launch marketing campaign

### Supporting Tasks
74. Create community forums and support channels
75. Publish video tutorials and documentation
76. Establish ongoing maintenance plan
77. Create roadmap for future development

## TODO

### IMMEDIATE REQUESTS
*None currently.*

### HIGH PRIORITY
78. Create CommandIDs for Preferences/Key Commands dialogs
79. Implement TreeCtrl wiring with panel registry in PrefUI
80. Implement panel lifecycle methods (Init, Load, Store) for all preference panels
82. Implement shared DSP infrastructure (AudioFX/AudioAnalysis): `DSP::SignalBus`, `DSP::ParameterSet`, `DSP::ModMatrix`, `DSP::LatencyBuffer`, `DSP::Analyzer` service hooks, and `DSP::PresetManager` with automation bridging to `UI::RackView`
83. Build vocal design and neural processing cores (AudioFX): `DSP::VoiceFeatureExtractor`, `DSP::HarmonyGenerator`, `DSP::StyleTransferNet`, `DSP::VoiceEncoder/Decoder`, `DSP::FormantMorpher`, and supporting gain/normalization stages
84. Implement mastering, loudness, and spectral control modules (AudioAnalysis/AudioFX): `DSP::LUFSMeter`, `DSP::ISPDetector`, `DSP::AutoGainScheduler`, `DSP::MasterAssistant`, `DSP::Stabilizer`, `DSP::ImpactShaper`, `DSP::PriorityAllocator`, and `DSP::DitherEngine`
85. Develop modulation, sequencing, and macro frameworks (AudioFX/AudioUI): `DSP::MotionSequencer`, `DSP::SceneMorph`, `DSP::StepSequencer`, `DSP::ModuleSwitcher`, `DSP::MacroController`, `UI::RackView`, `UI::SceneManager`, and `UI::XYPAD`
86. Implement synth voice architecture (AudioCore): `Synth::VoiceManager`, `Synth::ModMatrix`, `Synth::EnvelopeBank`, `Synth::LFOBank`, `Synth::WavetableOsc`, `Synth::OscillatorVA`, `Synth::FilterCascade`, `Synth::UnisonStack`, and `Synth::FormantShaper`
87. Implement sample streaming and articulation systems (Media/MediaPool): `Sample::StreamEngine`, `Sample::RoundRobin`, `Sample::LoopPool`, `Sample::SliceEngine`, `Sample::TimeStretch`, `Sample::ArticulationEngine`, `Sample::MicMixer`, `Sample::PedalModel`, `Sample::VintageDAC`, `Sample::DFDStream`, and `Sample::Zone`
88. Implement spatial calibration and immersive processing frameworks (Devices/AudioFX): `Calibration::MeasurementAnalyzer`, `Calibration::PhaseAnalyzer`, `Calibration::DelaySolver`, `DSP::FIRDesigner`, `DSP::IIRDesigner`, `DSP::AmbisonicsEncoder`, `DSP::BinauralRenderer`, `DSP::HeadTracker`, and `DSP::SurroundMeterBridge`
89. Implement rack and chain hosting infrastructure (Devices/AudioFX): `DSP::RackHost`, `DSP::ChainNode`, `DSP::MacroMapper`, `DSP::PresetBrowser`, `DSP::LatencyManager`, `NET::TransportLayer`, and `DSP::SessionManager` for StudioRack/StudioVerse workflows
92. Integrate `PluginSDK::GraphVisualization` with AudioUI rack/macro surfaces to render node/edge diagrams and active-path overlays
93. Build shared AI/groove/phrase services (`DSP::AIRecommender`, `Midi::GrooveExtractor`, `Midi::PhraseDatabase`) powering Bandmate-style suggestions across audio and MIDI stubs
### MEDIUM PRIORITY
81. Create .upp files for new packages with proper uses declarations
94. Extend `tools/generate_stubs.py` to regenerate new effect/instrument/MIDI packages with graph metadata and parameter scaffolding

### FUTURE CONSIDERATION
* Implement comprehensive error handling across all systems
* Add internationalization (i18n) support
* Design custom plugin API for third-party developers

## IN PROGRESS

* Organizing and prioritizing remaining TODO items in TASKS.md (Task 72-75)
* Updating project documentation and tracking systems

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
18. Extend MediaPool (Media package) with MediaSettings.h/.cpp
19. Create MIDI package with files: MidiChase.h/.cpp, MidiFilterConfig.h/.cpp, MidiDisplay.h/.cpp, MidiFilePrefs.h/.cpp
20. Create AudioEditing package with files: AudioImportPrefs.h/.cpp, TimeStretchPrefs.h/.cpp, SnapSettings.h/.cpp, FadeBehavior.h/.cpp
21. Create TransportPrefs package with files: TransportPrefs.h/.cpp
22. Create VSTHost package with files: VstHostPrefs.h/.cpp
23. Create ScoresEngine package with files: ScorePrefs.h/.cpp, ScoreColors.h/.cpp, ScoreEditingPrefs.h/.cpp, NoteLayerPrefs.h/.cpp
24. Create Video package additions with VideoPrefs.h/.cpp
25. Create Appearance package with InterfaceAdjust.h/.cpp, MixerPreview.h/.cpp
26. Add new methods to AudioCore/Transport.h as specified in design
27. Add new methods to AudioCore/Project.h as specified in design
28. Implement UI controls in PrefUI: Row, LabelBox, ColorRect, LabeledSlider, etc.
29. Create Devices package with files: Devices.h, Devices.cpp, AudioDeviceManager.h, AudioDeviceManager.cpp, MidiDeviceManager.h, MidiDeviceManager.cpp, PluginManager.h, PluginManager.cpp, ReWireHost.h, ReWireHost.cpp, VideoDevice.h, VideoDevice.cpp
30. Create Windowing package with files: Windowing.h, Windowing.cpp, Workspace.h, Workspace.cpp, WindowRegistry.h, WindowRegistry.cpp
31. Create HelpAbout package with files: HelpAbout.h, HelpAbout.cpp, Credits.h, Credits.cpp, Registration.h, Registration.cpp, WebLinks.h, WebLinks.cpp
32. Create Preferences package with files: Preferences.h, Preferences.cpp, KeyCommands.h, KeyCommands.cpp, Mapping.h, Mapping.cpp
33. Create Video package with files: Video.h, Video.cpp, AudioFromVideo.h, AudioFromVideo.cpp, ReplaceAudio.h, ReplaceAudio.cpp, Thumbnail.h, Thumbnail.cpp
34. Document generic instrument/effect specifications from REFERENCE_SOFTWARE.md and capture results in EFFECTS.md/INSTRUMENTS.md
35. Update root/packet `AGENTS.md` files to capture core class implementation details for EFFECTS/INSTRUMENTS blueprints
36. Generate effect/instrument stub packages and planning docs replacing commercial references in EFFECTS.md/INSTRUMENTS.md, including shared PluginSDK signal/data library
37. Expand stub coverage with additional effect/instrument families, MIDI-only processors, and graph visualisation hooks in PluginSDK
38. Document MIDI insert stubs, extract Transformer presets into scripts directory, and update roadmap
95. Re-analyze Roland ZENOLOGY reference material and update ZenCoreFxRack/ZenCoreWorkstation packages to match ZEN-Core architecture and shared repository code

## References

- See IMPLEMENTATION_ROADMAP.md for detailed phase breakdown
- See COMMAND_ARCHITECTURE_PLAN.md for technical architecture
- See COMMAND_CATEGORY_MAPPING.md for category-to-package mapping
- See CLASS_FUNCTION_REQUIREMENTS.md for detailed class/function specifications
