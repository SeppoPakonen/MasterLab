# Video Package

## Overview
The Video package handles video-related functionality including extracting audio from video, replacing audio in video files, and generating thumbnails. It provides tools for working with video content in the audio production environment.

## Key Components

### AudioFromVideo
- Extracts audio streams from video files
- Handles audio extraction with quality settings

### ReplaceAudio
- Replaces audio tracks in video files
- Manages audio-video synchronization

### Thumbnail
- Generates thumbnails from video files
- Handles thumbnail creation and saving

## Relations to Other Packages
- `FileIO`: File operations for video handling
- `MediaPool`: Integration with media pool for video assets

## Package Classes Relations
- All components work with video files
- AudioFromVideo and ReplaceAudio handle audio-video operations
- Thumbnail provides visualization capabilities