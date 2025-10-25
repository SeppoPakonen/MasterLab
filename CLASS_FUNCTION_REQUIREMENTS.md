# AudioMaster Class and Function Requirements

## Overview
This document details the specific classes and functions required to implement all commands listed in WINDOW_KEY_COMMANDS.md, organized by category.

## 1. FILE OPERATIONS (FileIO Package)

### Classes:
- FileManager
- ProjectSerializer
- AudioImporter
- MIDIImporter
- VideoImporter
- ExportManager
- BackupManager
- TemplateManager

### Key Functions:
```cpp
FileManager::NewProject()
FileManager::OpenProject(const String& path)
FileManager::SaveProject()
FileManager::SaveProjectAs(const String& path)
FileManager::CloseProject()
FileManager::RevertProject()
FileManager::ImportAudioFile(const String& path)
FileManager::ImportMIDIFile(const String& path)
FileManager::ImportVideoFile(const String& path)
FileManager::ExportAudioMixdown()
FileManager::ExportMIDILoop()
FileManager::PageSetup()
FileManager::Print()
```

## 2. EDIT OPERATIONS (ProjectMgmt Package)

### Classes:
- EditManager
- SelectionManager
- ClipboardManager
- HistoryManager
- UndoRedoStack

### Key Functions:
```cpp
EditManager::Copy()
EditManager::Cut()
EditManager::Paste()
EditManager::PasteAtOrigin()
EditManager::Delete()
EditManager::Duplicate()
EditManager::Undo()
EditManager::Redo()
EditManager::SelectAll()
EditManager::SelectNone()
EditManager::InvertSelection()
SelectionManager::SelectAllOnTracks()
SelectionManager::SelectInLoop()
SelectionManager::SelectFromCursorTo()
```

## 3. TRACK MANAGEMENT (AudioCore Package)

### Classes:
- TrackManager
- AudioManager
- MIDIManager
- InstrumentManager
- FolderManager
- GroupManager
- FXManager

### Key Functions:
```cpp
TrackManager::AddAudioTrack()
TrackManager::AddMIDITrack()
TrackManager::AddInstrumentTrack()
TrackManager::AddFolderTrack()
TrackManager::AddGroupTrack()
TrackManager::AddFXTrack()
TrackManager::RemoveTrack(TrackId id)
TrackManager::DuplicateTrack(TrackId id)
TrackManager::FoldTrack(TrackId id)
TrackManager::UnfoldTrack(TrackId id)
TrackManager::ToggleTrackFold(TrackId id)
```

## 4. AUDIO PROCESSING (AudioOps Package)

### Classes:
- AudioProcessor
- BounceProcessor
- FadeProcessor
- CrossfadeProcessor
- NormalizeProcessor
- TimeStretchProcessor
- PitchShiftProcessor
- AnalysisProcessor

### Key Functions:
```cpp
AudioProcessor::BounceSelection()
AudioProcessor::CrossfadeEvents()
AudioProcessor::NormalizeAudio()
AudioProcessor::TimeStretch()
AudioProcessor::PitchShift()
AudioProcessor::FadeIn()
AudioProcessor::FadeOut()
AudioProcessor::RemoveDCOffset()
AudioProcessor::Reverse()
AudioProcessor::Silence()
AudioProcessor::StereoFlip()
AudioProcessor::AnalyzeSpectrum()
AudioProcessor::CalculateStatistics()
```

## 5. MIDI PROCESSING (MidiOps Package)

### Classes:
- MIDIProcessor
- QuantizeProcessor
- TransposeProcessor
- LogicalEditor
- ControllerManager

### Key Functions:
```cpp
MIDIProcessor::Quantize()
MIDIProcessor::Transpose()
MIDIProcessor::FixedLength()
MIDIProcessor::FixedVelocity()
MIDIProcessor::Legato()
MIDIProcessor::DeleteOverlaps()
MIDIProcessor::IterativeQuantize()
MIDIProcessor::LogicalEdit()
MIDIProcessor::MergeTempoFromTapping()
MIDIProcessor::O-NoteConversion()
MIDIProcessor::PedalsToNoteLength()
```

## 6. AUTOMATION (AudioCore Package)

### Classes:
- AutomationManager
- ParameterAutomation
- AutomationTrack
- ReadWriteManager

### Key Functions:
```cpp
AutomationManager::ShowAutomation()
AutomationManager::HideAutomation()
AutomationManager::DeleteAutomation()
AutomationManager::SuspendReading()
AutomationManager::SuspendWriting()
AutomationManager::ToggleReadEnable()
AutomationManager::ToggleWriteEnable()
ParameterAutomation::RecordAutomation()
ParameterAutomation::PlayAutomation()
ParameterAutomation::ClearAutomation()
```

## 7. DEVICES (Devices Package)

### Classes:
- DeviceManager
- PluginManager
- MIDIDeviceManager
- AudioManager
- ControlRoom

### Key Functions:
```cpp
DeviceManager::SetupAudioDevices()
DeviceManager::SetupMIDIDevices()
DeviceManager::ManagePlugins()
DeviceManager::ConfigureControlRoom()
PluginManager::ScanForPlugins()
PluginManager::LoadPlugin(const String& path)
PluginManager::UnloadPlugin(PluginId id)
PluginManager::ShowPluginEditor(PluginId id)
```

## 8. MIXER (AudioCore Package)

### Classes:
- MixerManager
- ChannelStrip
- EQManager
- SendManager
- MeterManager

### Key Functions:
```cpp
MixerManager::ArmAllAudioTracks()
MixerManager::DisarmAllAudioTracks()
MixerManager::BypassEQs()
MixerManager::BypassInserts()
MixerManager::BypassSends()
MixerManager::HideAudioTracks()
MixerManager::HideMIDITracks()
MixerManager::LinkChannels()
MixerManager::UnlinkChannels()
ChannelStrip::SetVolume(float dB)
ChannelStrip::SetPan(float position)
ChannelStrip::SetMute(bool mute)
ChannelStrip::SetSolo(bool solo)
```

## 9. TRANSPORT (TransportUI Package)

### Classes:
- TransportManager
- LocatorManager
- CycleManager
- MetronomeManager
- PunchManager

### Key Functions:
```cpp
TransportManager::Play()
TransportManager::Stop()
TransportManager::Record()
TransportManager::Pause()
TransportManager::Rewind()
TransportManager::FastForward()
TransportManager::Locate(FrameIndex position)
TransportManager::SetLeftLocator()
TransportManager::SetRightLocator()
TransportManager::Cycle(bool enable)
TransportManager::PunchIn(bool enable)
TransportManager::PunchOut(bool enable)
MetronomeManager::Enable(bool enable)
MetronomeManager::SetTempo(float bpm)
MetronomeManager::SetSignature(int beats, int note)
```

## 10. PREFERENCES (Preferences Package)

### Classes:
- PreferenceManager
- AudioPrefs
- MIDIPrefs
- EditorPrefs
- ViewPrefs
- PluginPrefs

### Key Functions:
```cpp
PreferenceManager::LoadPreferences()
PreferenceManager::SavePreferences()
PreferenceManager::ResetPreferences()
PreferenceManager::ApplyAudioPreferences()
PreferenceManager::ApplyMIDIPreferences()
PreferenceManager::ApplyEditorPreferences()
PreferenceManager::ApplyViewPreferences()
PreferenceManager::ApplyPluginPreferences()
AudioPrefs::SetAudioCycleRecordMode(bool mode)
AudioPrefs::SetWaveformDisplay(bool show)
AudioPrefs::SetSnapToZeroCrossing(bool snap)
MIDIPrefs::SetMIDIThru(bool enable)
MIDIPrefs::SetNoteNameStyle(NoteNameStyle style)
EditorPrefs::SetAutoSelectEvents(bool enable)
EditorPrefs::SetLinkEditors(bool link)
```

## 11. VIEWS (Views Package)

### Classes:
- ViewManager
- ZoomManager
- NavigationManager
- DisplayManager
- LayoutManager

### Key Functions:
```cpp
ViewManager::ZoomIn()
ViewManager::ZoomOut()
ViewManager::ZoomToFit()
ViewManager::ZoomToSelection()
ViewManager::ZoomTracks(int count)
ViewManager::ToggleFullScreen()
ViewManager::NextView()
ViewManager::PreviousView()
NavigationManager::ScrollUp()
NavigationManager::ScrollDown()
NavigationManager::ScrollLeft()
NavigationManager::ScrollRight()
LayoutManager::SaveWorkspace()
LayoutManager::LoadWorkspace()
LayoutManager::ResetWorkspace()
```

## 12. TOOLS (Editors/Tools Package)

### Classes:
- ToolManager
- SelectTool
- DrawTool
- EraseTool
- SplitTool
- GlueTool
- TimeWarpTool
- CutTool

### Key Functions:
```cpp
ToolManager::SelectTool(ToolId tool)
ToolManager::GetCurrentTool()
ToolManager::SetToolOptions(const ToolOptions& options)
SelectTool::SelectEvents()
SelectTool::SelectRange()
SelectTool::AddToSelection()
DrawTool::CreateEvent()
DrawTool::ModifyEvent()
EraseTool::DeleteEvents()
SplitTool::SplitEvents()
GlueTool::JoinEvents()
TimeWarpTool::WarpAudio()
CutTool::TrimEvents()
```

## 13. PLUGINS (Devices/Plugins Package)

### Classes:
- PluginHost
- VSTWrapper
- AUWrapper
- AAXWrapper
- PluginParameter
- PluginPreset

### Key Functions:
```cpp
PluginHost::LoadPlugin(const String& path)
PluginHost::UnloadPlugin(PluginId id)
PluginHost::ProcessAudio(AudioBuffer& buffer)
PluginHost::ProcessMIDI(MIDIBuffer& buffer)
PluginHost::SetParameter(ParamId id, float value)
PluginHost::GetParameter(ParamId id)
PluginHost::SavePreset(const String& name)
PluginHost::LoadPreset(const String& name)
VSTWrapper::OpenEditor()
VSTWrapper::CloseEditor()
VSTWrapper::ResizeEditor(int width, int height)
```

## 14. SCRIPTS (Scripts Package)

### Classes:
- ScriptEngine
- LogicalProcessor
- PresetManager
- MacroRecorder
- ScriptManager

### Key Functions:
```cpp
ScriptEngine::ExecuteScript(const String& script)
ScriptEngine::CompileScript(const String& source)
ScriptEngine::LoadScript(const String& path)
ScriptEngine::SaveScript(const String& path, const String& source)
LogicalProcessor::ProcessProject(const LogicRules& rules)
LogicalProcessor::ProcessEvents(const LogicRules& rules)
PresetManager::SavePreset(const String& name, const ProcessChain& chain)
PresetManager::LoadPreset(const String& name)
PresetManager::DeletePreset(const String& name)
MacroRecorder::StartRecording()
MacroRecorder::StopRecording()
MacroRecorder::PlayMacro()
MacroRecorder::SaveMacro(const String& name)
```

## 15. MEDIA MANAGEMENT (MediaPool Package)

### Classes:
- MediaManager
- PoolManager
- ConformManager
- ConvertManager
- SearchManager
- ThumbnailManager

### Key Functions:
```cpp
MediaManager::ImportMedia(const String& path)
MediaManager::RemoveMedia(MediaId id)
MediaManager::FindMedia(const String& query)
MediaManager::GenerateThumbnails()
MediaManager::ReconstructMedia()
MediaManager::WriteAttributesToFile()
PoolManager::CreateFolder(const String& name)
PoolManager::DeleteFolder(FolderId id)
PoolManager::MoveMedia(MediaId id, FolderId folderId)
ConformManager::ConformFiles()
ConformManager::ConvertFiles()
SearchManager::SearchMediaBay(const String& query)
SearchManager::ResetSearch()
ThumbnailManager::GenerateCache()
ThumbnailManager::ClearCache()
```

## Integration Requirements

All classes must:
1. Inherit from a common base class for consistent command handling
2. Support serialization for project persistence
3. Provide undo/redo functionality through the command system
4. Integrate with the preference system for configurable behavior
5. Support plugin parameter automation where applicable
6. Provide appropriate observer patterns for UI updates
7. Handle threading considerations for real-time audio processing
8. Implement proper error handling and logging

## Command System Integration

Every function must be accessible through:
```cpp
CommandManager::Execute(CommandId id, const CommandContext& context)
CommandManager::CanExecute(CommandId id, const CommandContext& context)
CommandManager::GetCommandInfo(CommandId id)
```

This ensures consistent access to all functionality through the command system, enabling:
- Menu integration
- Keyboard shortcuts
- Scripting access
- Undo/Redo functionality
- Context-sensitive availability