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

## Relations to Other Packages
- `CtrlLib`: UI controls and framework for pool window
- `FileIO`: File operations for media handling
- `AudioCore`: Integration with audio content

## Package Classes Relations
- PoolWindow displays content managed by other components
- Conform and Convert work with media files
- Search provides discovery of media assets
- Integrity ensures media availability