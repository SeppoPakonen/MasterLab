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

### Calibration & Immersive Audio
- **`Calibration::MeasurementAnalyzer`** — Drives measurement sweeps, captures impulse responses, and feeds FIR/IIR solver pipelines.
- **`Calibration::PhaseAnalyzer`** / **`Calibration::DelaySolver`** — Compute sub/top phase alignment and recommended delay offsets.
- **`DSP::AmbisonicsEncoder`**, **`DSP::BinauralRenderer`**, and **`DSP::HeadTracker`** live here to support Nx, Abbey Road Studio 3, and DTS Neural workflows.
- **`DSP::SurroundMeterBridge`** acts as the multi-channel metering hub feeding AudioUI for immersive displays.

### Collaboration & Hosting Services
- **`NET::TransportLayer`** — Low-latency streaming engine for Waves Stream / remote collaboration, exposing secure channel negotiation and adaptive bitrate control.
- **`DSP::SessionManager`** — Coordinates StudioRack/StudioVerse remote sessions, handles preset sync, and integrates with PluginManager to load referenced plug-ins.
- **`DSP::RackHost`** / **`DSP::ChainNode`** — Managed by Devices when running plug-in chains outside the main process (live sound or network-hosted scenarios); shares implementation with AudioFX.

## Relations to Other Packages
- `CtrlLib`: UI controls and framework for device settings
- `AudioCore`: Integration with audio core for device handling
- `AudioFX`: Integration for plugin processing
- `AudioAnalysis`: Provides visualisation data for immersive metering.
- `AudioUI`: Renders calibration dashboards and stream controls.

## Package Classes Relations
- All managers provide different aspects of device connectivity
- PluginManager integrates with audio processing systems
- Audio and MIDI managers provide hardware interface
- Calibration, immersive audio, and collaboration layers plug into existing device lifecycle so hardware discovery, session sync, and routing live in one place.
