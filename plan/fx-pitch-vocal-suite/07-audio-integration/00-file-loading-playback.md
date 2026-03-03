# Task: Audio Playback and File Loading in Standalone

This task involves adding the ability to load a WAV file into the `PitchVocalSuite` standalone application and play it back while visualizing the waveform and pitch in real-time.

## Objective

To provide a "functional" test environment where the user can load a vocal track, see the detected pitch, and eventually hear the corrected output.

## Key Actions

1.  **Add "Open File" Button:**
    -   Implement a button in the `PitchVocalTopBar` to trigger a `FileSel`.
2.  **Integrate `WavFile` Loader:**
    -   Use the recently implemented `am::WavFile::Load` to populate a persistent `AudioBuffer` in the `PitchVocalProcessor`.
3.  **Real-time Playback (Mock):**
    -   Implement a basic playback cursor (playhead) that moves across the waveform.
    -   Since standalone playback via ALSA/JACK is a large task, initially support "Offline Analysis Visualization" where the entire file is analyzed upon loading and displayed in the graph.
4.  **UI Updates:**
    -   Update `WaveformStrip` to show the entire loaded file's overview.
    -   Update `PitchGraphEditor` to show the entire detected pitch curve for the file.

## Acceptance Criteria

1.  Clicking "Open" allows selecting a WAV file.
2.  The waveform overview is displayed in the `WaveformStrip`.
3.  The detected pitch for the entire file is displayed in the `PitchGraphEditor`.
4.  The user can navigate (scroll/zoom) through the loaded audio data.

## Risks

- **Memory Usage:** Loading very large WAV files into memory. (Mitigation: Use a peak-only cache for long waveforms).
- **Analysis Time:** Analyzing a 5-minute vocal track in one go might hang the UI. (Mitigation: Perform analysis in a background `CoWork` thread).
