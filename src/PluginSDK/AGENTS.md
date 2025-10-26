# PluginSDK Package — Internal Plug-in Interface

## Overview
PluginSDK defines the lightweight processor interfaces, signal bus abstractions, graph visualisation helpers, and parameter utilities required by the stubbed instruments, effects, and MIDI processors. It mimics a pared-down VST-style contract so individual processors can be developed and tested in isolation before hooking into the full Ultimate++ host.

## Core Types
- `AudioConfig` — Carries sample-rate, block size, and channel layout reported by the host.
- `AudioBus` — View over interleaved or planar channel buffers; exposes helper methods for channel counts and frame operations.
- `ProcessContext` — Bundles audio buses, automation snapshots, tempo, transport state, and side-chain/control data for each processing block.
- `NoteEvent` / `ControlEvent` — Lightweight MIDI-style events for instrument processors.

## Processor Interfaces
- `PluginProcessor` — Base class for insert effects. Declares `Prepare`, `Process`, `Reset`, parameter setters/getters, and exposes a `GraphVisualization` descriptor for UI rendering.
- `InstrumentProcessor` — Extends `PluginProcessor` with `NoteOn`, `NoteOff`, and `AllNotesOff` hooks for voice management.
- `MidiEffectProcessor` — Handles MIDI-only processors with `Process(ctx, midiIn, midiOut, ctlIn, ctlOut)`, parameter API, and graph descriptor.
- `MidiInstrumentProcessor` — Generates MIDI phrases (EZkeys/EZdrummer style) via `GeneratePattern`, sitting on top of the MIDI effect base.
- `AnalyzerTap` — Optional mix-in providing access to analysis buses for metering/visualisation.

## Parameter, Routing & Graph Helpers
- `ParameterSet` — Registers automatable parameters, value ranges, and smoothing coefficients; exposes typed accessors.
- `ModulationBus` — Represents per-sample modulation/control lanes shared between macro controllers and processors.
- `RoutingMap` — Describes complex audio/control signal topologies required by multi-module processors.
- `GraphVisualization` — Contains node/edge metadata so GUIs can draw internal signal/data flow with active path highlighting.

## Collaboration Notes
- All instrument/effect stubs in `effects/`, `instruments/`, `midi_effects/`, and `midi_instruments/` depend on PluginSDK.
- Future host integration should translate Ultimate++ audio engine buffers into `ProcessContext` instances, enabling drop-in replacement of commercial plug-ins with our custom stubs.
