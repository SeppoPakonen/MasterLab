# Task: Advanced Pitch Detection (Autocorrelation)

This task involves replacing the skeleton ZCR pitch detector with a more robust FFT-based autocorrelation algorithm.

## Objective

To improve pitch detection accuracy for monophonic vocal signals by implementing the Wiener-Khinchin theorem (Autocorrelation via FFT).

## Key Actions

1.  **Implement FFT-based Autocorrelation:** [DONE]
    -   Window the input signal (e.g., Hann or Hamming window).
    -   Zero-pad to double the window size.
    -   Perform `RealFFT`.
    -   Calculate the power spectrum (magnitude squared).
    -   Perform `InverseRealFFT` to get the autocorrelation function.
2.  **Peak Detection:** [DONE]
    -   Find the highest peak in the autocorrelation function within a reasonable pitch range (e.g., 50Hz to 1500Hz).
    -   Implement parabolic interpolation for sub-bin peak accuracy.
3.  **Confidence Estimation:** [DONE]
    -   Use the peak magnitude relative to the zero-lag autocorrelation (signal energy) as a confidence measure.
4.  **Refactor `PitchAnalysisEngine`:** [DONE]
    -   Update `Analyze()` to use the new algorithm.

## Acceptance Criteria

1.  The detected pitch is significantly more stable than the ZCR estimator. [DONE]
2.  The engine correctly identifies pitches for sustained vocal-like tones. [DONE]
3.  Performance is maintained for real-time operation. [DONE]

## Risks

- **Computational Cost:** Two FFTs per analysis window might be heavier than ZCR. (Mitigation: Only analyze at the hop rate, which is already done).
- **Octave Errors:** Autocorrelation is prone to picking harmonics or sub-harmonics. (Mitigation: Implement basic peak pruning or "best candidate" logic).
