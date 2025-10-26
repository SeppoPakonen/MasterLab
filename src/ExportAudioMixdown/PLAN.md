# ExportAudioMixdown Plan

## Deliverables
- Functional export dialog mirroring Cubase 5 layout
- Dynamic codec option rendering (WAV, AIFF, MP3, Ogg, WMA, Wave64)
- Channel batch export tree with per-channel selection states
- Progress + cancel window for background renders
- ID3 metadata editor for MP3 exports

## Upcoming Steps
1. Replace placeholder codec metadata with structures from `FileIO::MediaFormatRegistry`.
2. Integrate `ProjectMgmt::CommandManager` to trigger exports through the command system instead of direct callbacks.
3. Populate channel tree with real project channels (Outputs, Groups, FX, Instruments) pulled from `AudioCore::Mixer` and `ProjectMgmt::Selection`.
4. Implement validation so Export button enables only when filename, path, and channel selection are valid.
5. Connect `WhenBrowsePath` to platform-specific folder pickers and persist last-used directories.
6. Feed progress dialog with real-time render updates from the export job queue.

## Long-Term Goals
- Support preset management for export configurations.
- Allow multi-format batch exports with per-format option overrides.
- Expose loudness normalization targets and mixdown analysis once AudioAnalysis modules are ready.
