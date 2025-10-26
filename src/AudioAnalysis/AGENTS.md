# AudioAnalysis Package

## Overview
The AudioAnalysis package provides various audio analysis tools including spectrum analyzer, statistics, hitpoint detection, and warping functionality. These tools are used for analyzing and processing audio content.

## Key Components

### Spectrum
- Provides spectrum analysis functionality
- Calculates frequency domain representation
- Will expose `RenderFFT(const AudioFrame& frame)` for plug-in metering and provide windowing utilities shared with `DSP::Analyzer`.

### Statistics
- Calculates statistical properties of audio
- Provides RMS, peak, and other measurements
- Extends to loudness standards via `DSP::LUFSMeter::IntegrateMomentary()` and `DSP::LUFSMeter::IntegrateShortTerm()`.

### Hitpoints
- Detects hitpoints in audio content
- Used for slicing and groove detection

### Warp
- Provides audio warping functionality
- Allows for time stretching without pitch change

## Relations to Other Packages
- `AudioCore`: Integration with audio data structures
- `AudioFX`: Integration with audio effects processing
- `CtrlLib`: UI elements for visualization tools
- `Devices`: Shares Ambisonics and head-tracking telemetry for immersive metering workflows.

## Package Classes Relations
- All components work with audio data from AudioCore
- Spectrum, Statistics, and Hitpoints provide analysis information
- Warp provides audio manipulation capabilities
- `DSP::Analyzer` serves as the central analysis façade used by effects; it orchestrates `Spectrum`, `Statistics`, `LUFSMeter`, and `TruePeakDetector` instances.
- `DSP::TruePeakDetector` offers `ProcessBlock` with 4x/8x oversampling for ISP detection feeding maximisers.
- `DSP::MaskingAnalyzer` compares primary vs sidechain spectra, delivering energy heatmaps consumed by Equator/Neutron-style processors.
- `DSP::LoggingBackend` (shared with metering plug-ins) records time-stamped measurement series to disk/automation lanes.
