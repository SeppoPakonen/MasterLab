# ScoresEngine Package

## Overview
The ScoresEngine package handles notation-specific preferences including score colors, editing preferences, and note layer visibility. It provides the configuration layer for notation display and editing throughout the application.

## Key Components

### ScorePrefs
- Manages general score preferences and settings

### ScoreColors
- Handles color rules for different notation elements
- Controls how different events are colored in the score

### ScoreEditingPrefsManager
- Manages score editing behavior preferences
- Controls cursor behavior, visual feedback, and editing options

### NoteLayerPrefsManager
- Controls visibility and weight of different notation elements
- Manages how various elements are displayed in the notation

## Relations to Other Packages
- `Scores`: Integration with notation engine and display
- `Editors`: Integration with score editor functionality

## Package Classes Relations
- All components work together to control notation appearance and behavior
- Preferences affect how notation is displayed and edited
- Settings are applied during score display and editing operations