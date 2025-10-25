# VSTHost Package

## Overview
The VSTHost package handles VST plugin host preferences including global VST settings, metering preferences, and control room options. It provides the configuration layer for VST plugin management throughout the application.

## Key Components

### VstHostPrefsManager
- Manages all VST host-related preferences and settings
- Controls behavior of the VST plugin system

### VstGlobalPrefs
- Contains global VST plugin settings
- Controls auto-connect, suspension, sorting, and UI behavior

### MeteringPrefs
- Handles metering preferences for VST plugins
- Controls peak hold times and fallback rates

### ControlRoomPrefs
- Manages control room-specific preferences
- Controls talkback, volume display, and studio settings

## Relations to Other Packages
- `Devices`: Integration with plugin manager functionality
- `AudioFX`: Integration with audio effects processing
- `AudioCore`: Integration with audio processing system

## Package Classes Relations
- VstHostPrefsManager coordinates all VST host preferences
- Preferences affect how plugins are loaded, managed, and displayed
- Settings are applied to PluginManager and audio processing systems