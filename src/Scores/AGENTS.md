# Scores Package

## Overview
The Scores package handles music notation functionality including the notation model, layout engine, and notation functions. It provides the foundation for displaying and editing musical scores in traditional notation format.

## Key Components

### NotationModel
- Represents the musical content in score format
- Stores measures, notes, and musical attributes

### LayoutEngine
- Handles the visual layout of musical notation
- Manages page sizing, margins, and formatting

### Functions
- Provides notation-specific operations like transposition and quantization
- Handles score validation and processing

## Relations to Other Packages
- `CtrlLib`: UI controls and framework for score display
- `Draw`: Drawing functionality for notation rendering
- `Editors`: Integration with score editor components

## Package Classes Relations
- NotationModel provides data structure for scores
- LayoutEngine formats the notation for display
- Functions provide operations that work on the notation model