# TransportUI Package

## Overview
The TransportUI package handles the transport panel UI and related controls including metronome, cycle range, and pre/post-roll controls. It integrates with the AudioCore transport system to provide a complete transport control interface.

## Key Components

### Metronome
- Controls metronome functionality
- Handles volume, sound, and enable settings

### CycleRange
- Manages cycle/loop range settings
- Controls looping behavior during playback

### PrePostRoll
- Handles pre-roll and post-roll functionality
- Allows for lead-in and lead-out time during playback/recording

## Relations to Other Packages
- `CtrlLib`: UI controls and framework for transport panel
- `AudioCore`: Integration with the core transport system

## Package Classes Relations
- All components interact with the AudioCore::Transport system
- Metronome provides audio feedback during transport operations
- CycleRange controls the looping behavior of the transport
- PrePostRoll provides timing controls for precise playback/recording