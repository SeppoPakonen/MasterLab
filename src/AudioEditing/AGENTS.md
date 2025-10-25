# AudioEditing Package

## Overview
The AudioEditing package handles audio editing preferences and settings including import preferences, time stretch algorithms, snap settings, and fade behavior. It provides the configuration layer for audio editing operations throughout the application.

## Key Components

### AudioImportPrefsManager
- Manages audio import preferences and settings
- Controls how audio files are imported into the project

### TimeStretchPrefsManager
- Handles time stretch algorithm preferences
- Manages algorithm selection and related options

### SnapSettingsManager
- Controls snap-to-grid and other alignment behaviors
- Manages snap tolerance and target preferences

### FadeBehaviorManager
- Manages fade curve behavior and appearance
- Controls how fade handles and curves are displayed

## Relations to Other Packages
- `AudioCore`: Integration with core audio processing
- `AudioOps`: Integration with audio operations and effects

## Package Classes Relations
- All components work together to control audio editing behavior
- Preferences affect how audio content is processed and displayed
- Settings are applied during editing operations in the editors