# TransportPrefs Package

## Overview
The TransportPrefs package handles transport-related preferences including playback behavior, scrub settings, timecode preferences, and wind options. It provides the configuration layer for transport operations throughout the application.

## Key Components

### TransportPrefsManager
- Manages all transport-related preferences and settings
- Controls behavior of the transport system

### TransportBehavior
- Contains all settings for transport behavior
- Includes punch, cursor, locating, and winding preferences

### ScrubPrefs
- Handles scrub preferences for playback behavior
- Controls response and volume during scrub operations

### TimecodePrefs
- Manages timecode display and behavior preferences
- Controls frame rate and cursor settings

### WindOptions
- Controls winding behavior during playback
- Manages speed factors for fast winding

## Relations to Other Packages
- `AudioCore`: Integration with the transport system in audio core

## Package Classes Relations
- TransportPrefsManager manages all transport preferences
- Settings are applied to the Transport system to modify behavior
- Preferences affect how the transport responds to user commands