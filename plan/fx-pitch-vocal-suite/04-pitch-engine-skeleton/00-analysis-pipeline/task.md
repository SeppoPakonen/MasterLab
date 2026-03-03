# Task: Pitch Engine Analysis Pipeline (Skeleton)

This task involves creating a skeleton for the pitch detection and analysis pipeline of the `PitchVocalSuite`.

## Objective

To establish a data flow from raw audio samples to a pitch/time representation that the `PitchGraphEditor` can visualize.

## Key Actions

1.  **Define `PitchAnalysisEngine` Interface:**
    -   `Analyze(const AudioBuffer& buffer)`
    -   `GetPitchAt(double time)`
2.  **Integrate `AudioAnalysis`:**
    -   Use existing autocorrelation or FFT-based methods from `src/AudioAnalysis/`.
3.  **Implement Data Store:**
    -   Store detected pitch points with timestamps.
    -   Support efficient range queries for UI rendering.
4.  **Skeleton Implementation:** [DONE]
    -   A minimal "mock" or basic autocorrelation detector to prove the pipeline. [COMPLETED WITH ZCR ESTIMATOR]

## Acceptance Criteria

1.  The engine can process an input audio buffer and produce a series of pitch points.
2.  The UI can query and display these pitch points (initially as a simple console output or basic visualization).
3.  The pipeline is thread-safe and can handle real-time or offline processing.

## Risks

- **Computational Complexity:** Pitch detection can be CPU-intensive; optimization may be needed.
- **Latency:** Real-time correction requires a low-latency analysis window.
- **Accuracy:** Skeleton might have poor tracking; refinement will be needed in later phases.
