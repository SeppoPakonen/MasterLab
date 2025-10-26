# ExportAudioMixdown Package

## Overview
Provides the Cubase 5 style export audio mixdown dialog.  The package contains the window shell, channel selection tree, codec option panel, and the progress/ID3 editor placeholders described in `cubase5_export_audio_mixdown.md`.  The scaffolding allows FileIO and AudioCore subsystems to attach render pipelines later without rewriting UI composition.

## Key Classes

- **ChannelTreePane** — Wraps a `TreeCtrl` with channel groups (`Output`, `Group`, `FX`, `Instrument`).  Exposes `SetChannels(const ExportChannels&)` so callers can populate project-specific nodes, and `GatherSelection()` to compute which channels should be rendered.
- **CodecOptionsPane** — Dynamic panel that swaps between codec-specific option forms (WAV broadcast flags, MP3 bitrate/sample-rate selections, etc.).  Extensible via `RegisterLayout` for future codecs.
- **ExportAudioMixdownDialog** — `TopWindow` hosting the splitter, path/filename editors, codec drop-down, export flags, and action buttons.  Provides helper events (`WhenExport`, `WhenClose`) plus methods to bind recent path lists, sample rate enumerations, and format availability.
- **ID3TagDialog** — Modal pop-up used by the MP3 codec panel to collect metadata (Title, Artist, Album, Year, Genre, Comment).  Currently uses simple edit fields with placeholder validation.
- **ExportProgressDialog** — Modal progress window with progress bar and cancel button, preparing for asynchronous render jobs.

## Responsibilities

- Mirror the control hierarchy documented in the Cubase reference: left channel selection pane, right configuration form, codec-specific widgets, export/post-export flags, and action buttons.
- Provide neutral data structures (`ExportRequest`, `ChannelSelection`) so FileIO can trigger render jobs without depending on UI classes.
- Surface callbacks for browse dialogs, export execution, ID3 editing, and closing to integrate with yet-to-be-implemented command managers.

## Future Work (see PLAN.md)

- Populate channel tree from `ProjectMgmt::Project` model and reflect selection states.
- Connect codec option pane to `FileIO::MediaFormatRegistry` for real codec metadata and validation.
- Wire export execution to asynchronous job queue with progress updates and cancellation support.
- Persist last-used export settings per project and restore them on dialog creation.
- Localize UI strings once i18n framework is introduced.
