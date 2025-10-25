# Browser Package

## Overview
The Browser package handles content discovery through various types of browsers including Media Bay, Loop Browser, and Sound Browser. It also provides tagging functionality for organizing and categorizing media assets.

## Key Components

### MediaBay
- Provides a general media browser interface
- Allows browsing of various media types

### LoopBrowser
- Specialized browser for loop content
- Optimized for finding and auditioning loops

### SoundBrowser
- Specialized browser for sound content
- Provides sound-specific browsing features

### Tagging
- Handles tagging of media files
- Provides organization through metadata

## Relations to Other Packages
- `CtrlLib`: UI controls and framework for browser windows
- `MediaPool`: Integration with media pool functionality
- `AudioCore`: Integration with audio content

## Package Classes Relations
- All browser windows provide different interfaces to media content
- Tagging system supports organization across all browser types