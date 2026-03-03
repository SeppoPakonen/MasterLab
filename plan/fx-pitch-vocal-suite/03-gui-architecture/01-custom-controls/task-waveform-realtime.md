# Task: Real-time Waveform Visualization

This task involves updating the `WaveformStrip` to display the actual audio waveform being processed by the `PitchVocalProcessor`.

## Objective

To replace the dummy sine-wave visualization with a real-time rolling buffer of audio samples from the processor.

## Key Actions

1.  **Add Sample Buffer to `PitchVocalProcessor`:**
    -   Implement a thread-safe rolling sample buffer (e.g., a simple `Vector<float>` or specialized ring buffer).
    -   Store the last N samples (e.g., 4096 or more) during `Process()`.
2.  **Update `WaveformStrip`:**
    -   Add a `SetProcessor()` method or access the processor via the parent `PitchVocalEditor`.
    -   In `Paint()`, read the sample buffer from the processor and render the peaks.
3.  **Optimize Rendering:**
    -   Instead of drawing every sample, draw min/max peaks for each pixel column to ensure performance.

## Acceptance Criteria

1.  The `WaveformStrip` displays a moving waveform that reacts to input audio.
2.  The visualization is smooth and does not cause UI lag.
3.  The implementation is thread-safe (UI reading samples while the audio thread writes them).

## Risks

- **Thread Contention:** Frequent locking of the sample buffer could impact audio performance. (Mitigation: Use a double-buffer or atomic head/tail pointers).
