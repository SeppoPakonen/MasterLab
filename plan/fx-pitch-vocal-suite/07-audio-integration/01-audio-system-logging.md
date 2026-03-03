# Task: Audio System and Debug Logging

This task involves integrating a real-time audio playback system and a robust logging interface for diagnostics in the standalone `PitchVocalSuite`.

## Objective

To provide audible feedback and visibility into the background processing (pitch detection, correction).

## Key Actions

1.  **Integrate `CtrlLog`:** [DONE]
    -   Add `CtrlLog` to `PitchVocalEditor`.
    -   Use a `Splitter` to show the editor on top and the log at the bottom.
    -   Redirect processor messages to this log.
2.  **Implement Audio Playback (Standalone):** [DONE]
    -   Use `Portaudio::AudioDeviceStream` from the `ai-upp/SoftAudio` package.
    -   Initialize the audio stream in `GUI_APP_MAIN`.
    -   Implement a callback that pulls samples from the `PitchVocalProcessor`.
3.  **Refine `PitchVocalProcessor` for Real-time:** [DONE]
    -   Ensure `Process()` is thread-safe and optimized for the audio callback.
    -   Add diagnostic logging during analysis (e.g., "Detected pitch: X Hz").

## Acceptance Criteria

1.  The standalone application produces sound when playing the loaded audio file. [DONE]
2.  A diagnostic log window is visible and populated with real-time analysis data. [DONE]
3.  The application adheres to the shared `CtrlLog` pattern. [DONE]

## Risks

- **Real-time Threading:** Logging from the audio thread can cause dropouts. (Mitigation: Use a lock-free message queue to send logs to the UI thread).
- **Portaudio Configuration:** Configuring the correct device and sample rate on Gentoo Linux. (Mitigation: Default to the system's default device).
