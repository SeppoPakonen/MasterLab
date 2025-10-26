# PluginSDK Package — Internal Plug-in Interface

## Overview
PluginSDK defines the lightweight processor interfaces, signal bus abstractions, and parameter utilities required by the stubbed instruments and effects. It mimics a pared-down VST-style contract so individual processors can be developed and tested in isolation before hooking into the full Ultimate++ host.

## Core Types
- `AudioConfig` — Carries sample-rate, block size, and channel layout reported by the host.
- `AudioBus` — View over interleaved or planar channel buffers; exposes helper methods for channel counts and frame operations.
- `ProcessContext` — Bundles audio buses, automation snapshots, tempo, transport state, and side-chain/control data for each processing block.
- `NoteEvent` / `ControlEvent` — Lightweight MIDI-style events for instrument processors.

## Processor Interfaces
- `PluginProcessor` — Base class for insert effects. Declares `Prepare`, `Process`, `Reset`, and parameter setters/getters.
- `InstrumentProcessor` — Extends `PluginProcessor` with `NoteOn`, `NoteOff`, and `AllNotesOff` hooks for voice management.
- `AnalyzerTap` — Optional mix-in providing access to analysis buses for metering/visualisation.

## Parameter & Routing Helpers
- `ParameterSet` — Registers automatable parameters, value ranges, and smoothing coefficients; exposes typed accessors.
- `ModulationBus` — Represents per-sample modulation/control lanes shared between macro controllers and processors.
- `RoutingMap` — Describes complex audio/control signal topologies required by multi-module processors.

## Collaboration Notes
- All instrument/effect stubs in `effects/` and `instruments/` depend on PluginSDK.
- Future host integration should translate Ultimate++ audio engine buffers into `ProcessContext` instances, enabling drop-in replacement of commercial plug-ins with our custom stubs.
