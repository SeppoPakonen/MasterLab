# Task: Basic Pitch Shifting (Functional Engine)

This task involves implementing the first actual audio processing logic in the `PitchVocalProcessor` to correct the pitch towards the target notes.

## Objective

To replace the bypass "mockup" with a functional pitch-shifting DSP engine.

## Key Actions

1.  **Implement Basic Pitch Shifter:**
    -   Choice: Simple Delay-line based (variable tap) or basic SOLA (Synchronous Overlap and Add).
    -   Location: `src/DSP/PitchShifter.h`.
2.  **Connect Retune Logic:**
    -   Calculate the `shiftRatio` based on `detectedPitch` and `targetNote` (from manual note objects).
    -   Apply the `correctionSpeed` parameter to smooth the transition.
3.  **Process Audio:**
    -   In `PitchVocalProcessor::Process`, detected pitch is used to drive the `PitchShifter`.
    -   Input samples are processed and written to the output buffer.

## Acceptance Criteria

1.  Input audio is pitch-shifted in real-time.
2.  The output follows the target notes (to a basic degree of quality).
3.  The algorithm is shared via the `src/DSP` package.

## Risks

- **Phase Artifacts:** Simple pitch shifting often introduces robotic or metallic artifacts. (Mitigation: Implement Formant Preservation in a later task).
- **Latency:** Pitch detection and shifting both introduce latency. (Mitigation: Report latency to host via `PluginSDK`).
