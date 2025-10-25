# Devices Package

## Overview
The Devices package handles all device management including audio devices, MIDI devices, plugin management, ReWire connectivity, and video devices. It provides a unified interface for managing all external hardware and software components.

## Key Components

### AudioDeviceManager
- Manages audio input and output devices
- Handles device enumeration and selection

### MidiDeviceManager
- Manages MIDI input and output devices
- Handles MIDI device connection and disconnection

### PluginManager
- Discovers and manages audio plugins (VST, LV2, LADSPA, CLAP)
- Handles plugin scanning and cache management

### ReWireHost
- Manages ReWire connectivity
- Handles connection to other ReWire applications

### VideoDevice
- Manages video input devices
- Handles video capture functionality

## Relations to Other Packages
- `CtrlLib`: UI controls and framework for device settings
- `AudioCore`: Integration with audio core for device handling
- `AudioFX`: Integration for plugin processing

## Package Classes Relations
- All managers provide different aspects of device connectivity
- PluginManager integrates with audio processing systems
- Audio and MIDI managers provide hardware interface