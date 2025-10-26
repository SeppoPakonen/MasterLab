# MediaPool Package

## Overview
The MediaPool package handles the central asset pool functionality including media pool window, conform/convert operations, search capabilities, and integrity checking. It serves as the central repository for all media assets used in projects.

## Key Components

### PoolWindow
- Provides the UI for the media pool
- Displays assets in the pool

### Conform
- Handles media conformity operations
- Ensures media meets project requirements

### Convert
- Handles media format conversion
- Converts media to desired formats

### Search
- Provides search functionality across the media pool
- Allows finding specific assets

### Integrity
- Checks the integrity of media in the pool
- Verifies that media files are accessible and valid

## Sample Playback & Instrument Assets
- `Sample::StreamEngine` (Media package) performs disk streaming for large instruments; MediaPool coordinates prefetch caching and purge thresholds.
- `Sample::RoundRobin`, `Sample::ArticulationEngine`, and `Sample::MicMixer` provide articulation management for Kontakt-style libraries; Pool metadata tracks mappings so `AudioCore` can request the right assets at load time.
- `Sample::LoopPool`, `Sample::SliceEngine`, and `Sample::TimeStretch` support Momentum-style loop remixing; search/indexing exposes slice descriptors for quick audition.

## Relations to Other Packages
- `CtrlLib`: UI controls and framework for pool window
- `FileIO`: File operations for media handling
- `AudioCore`: Integration with audio content
- `AudioFX`: Accesses analysis metadata (transients, pitch) generated during ingestion for transient-aware processors.

## Package Classes Relations
- PoolWindow displays content managed by other components
- Conform and Convert work with media files
- Search provides discovery of media assets
- Integrity ensures media availability
