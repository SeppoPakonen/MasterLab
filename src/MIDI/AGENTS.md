# MIDI Package

## Overview
The MIDI package handles MIDI-specific functionality including chase events, filter configurations, display preferences, and file import/export settings. It provides the infrastructure for managing MIDI behavior throughout the application.

## Key Components

### MidiChase
- Manages MIDI chase event preferences
- Controls which events are chased (note, controller, pitchbend, etc.)

### MidiFilterConfig
- Handles MIDI filtering settings
- Manages record/thru filters and channel blocking

### MidiDisplay
- Controls MIDI display preferences
- Manages note name styles and controller visibility

### MidiFilePrefs
- Manages import/export preferences for MIDI files
- Handles both import and export specific settings

## Relations to Other Packages
- `AudioCore`: Integration with MIDI processing in audio core
- `Editors`: Integration with MIDI editors to apply display preferences

## Package Classes Relations
- All components work together to provide complete MIDI handling
- Preferences affect how MIDI events are processed and displayed
- File preferences control import/export behavior