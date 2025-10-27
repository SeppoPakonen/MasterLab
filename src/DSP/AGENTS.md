# DSP Package

## Overview
The DSP package contains shared digital signal processing infrastructure that is referenced by both AudioFX and AudioCore packages. This package provides common components like signal routing, parameter management, modulation systems, latency handling, preset management, analysis tools, vocal processing, and other shared DSP utilities that multiple audio processing components rely on.

## Key Components

### SignalBus
- Manages multi-channel audio frames and consolidates bus formats (mono/stereo/surround)
- Provides helpers like `AcquireBlock(int frames)` and `Route(const BusLayout& src, const BusLayout& dst)` for sample-accurate routing with latency accounting
- Handles inter-package audio data flow between effects, instruments, and analysis modules

### ParameterSet
- Registers automatable parameters and performs smoothing with `ApplySmoothing(double milliseconds)`
- Emits host descriptors and integrates with automation to resolve parameter IDs
- Provides the foundation for effect and instrument parameter automation

### ModMatrix
- Implements normalized modulation matrix with `AddSource`, `AddDestination`, and `ComputeConnections()` 
- Produces per-sample modulation buffers driven by LFOs, envelopes, MIDI, or macro controllers
- Shared between instrument and effect implementations

### LatencyBuffer
- Provides `Configure(int lookahead)` and `Process(BufferView in, BufferView out)` to support look-ahead stages
- Reports latency to host and to `SignalBus` for proper timing alignment

### PresetManager
- JSON-backed preset service with core methods: `LoadPreset(const String& id)`, `StorePreset(const Preset& preset)`, and `EnumerateLibrary()`
- Bridges to automation system for parameter automation tracking
- Shared between internal FX and exported plug-ins

### Analyzer
- Base class for various DSP analyzers with `ProcessBlock`, `GetResults`, `Reset`, and `Configure` methods
- Includes `SpectrumAnalyzer`, `LUFSMeter`, and `ISPDetector` implementations
- Provides analysis services for loudness, spectrum, peak detection and other audio measurements

### Vocal Processing Components
- **`VoiceFeatureExtractor`** - Extracts pitch, formants, spectral flux with core methods: `AnalyzeBlock`, `GetPitchTrack()`, `GetFormantProfile()` forming the foundation for Omnivox and Nectar harmony engines
- **`HarmonyGenerator`** - Generates detuned/delayed harmonies with `RenderVoices(const HarmonySetup&)` for harmony generation
- **`StyleTransferNet`** - Runtime wrapper around neural voice style models with `LoadModel`, `ProcessFrame` for neural style transfer
- **`FormantMorpher`** - Applies vocal tract length transformations with `ConfigureTargets` and `Process` methods
- **`VoiceEncoder`** / **`VoiceDecoder`** - Low-latency neural codec pair supporting Replay voice conversion with `Encode`/`Decode` methods

### ZenCoreMFXCatalogue
- Central registry of Zen-Core MFX/TFX algorithms with metadata flags (category, combination support)
- Used by ZenCoreFxRack and model-expansion presets for algorithm management

## Relations to Other Packages
- `AudioCore`: Used for voice management and synthesis parameter modulation
- `AudioFX`: Used for effect parameter modulation, routing, algorithm registry, and analysis
- `AudioAnalysis`: Provides analysis tools that may need parameter sets
- `PluginSDK`: Used for plugin parameter handling and preset management
- `Devices`: Shares spatial and calibration engines

## Package Classes Relations
- SignalBus provides the foundation for all audio data routing in the system
- ParameterSet provides the foundation for automation across all parameterized components
- ModMatrix provides modulation routing shared between instruments and effects
- LatencyBuffer ensures proper timing alignment for look-ahead processing
- PresetManager provides unified preset handling across all DSP components
- Analyzer provides signal analysis services for measurement and visualization
- Vocal processing components provide voice-specific analysis, synthesis, and transformation
- ZenCoreMFXCatalogue provides central algorithm registry for ZEN-Core compatible systems