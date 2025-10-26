# MediaPool Plan

## Immediate Enhancements
1. Connect toolbar actions to Playback/Transport so Play/Loop audition audio through the preview bus.
2. Populate list rows from `MediaPool::Repository` with real metadata (usage count, algorithm, waveform preview handles).
3. Hook search dialog to `MediaPool::Search` backend; map scope dropdown to repository queries.
4. Persist column visibility and status bar toggle per user profile.

## Medium-Term Goals
- Implement waveform thumbnail rendering cache and refresh invalid entries when files change.
- Integrate integrity checks to highlight missing media directly in the list (Status column icons).
- Support drag-and-drop of pool items into the project area.
- Add context menu actions (Insert into Project, Reveal in Finder, Convert Files, etc.).

## Long-Term Goals
- Enable background indexing progress indicators and multi-threaded waveform generation.
- Provide filtering facets similar to MediaBay (tags, tempo range, key) with live updates.
- Allow configurable column layouts per media type (audio/video).
