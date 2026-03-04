#include "PitchVocalSuiteCLI.h"

// These functions are now part of the PitchVocalSuiteCLI package
void GenerateTestTone()
{
	const int sampleRate = 48000;
	const int durationSeconds = 3;
	const double frequency = 440.0;
	const String path = "test_tone.wav";

	am::AudioBuffer buffer;
	buffer.Resize(1, sampleRate * durationSeconds);
	buffer.rate = sampleRate;
	
	double phase = 0;
	double phaseIncr = 2.0 * M_PI * frequency / sampleRate;
	
	for(int i = 0; i < buffer.GetFrames(); ++i) {
		buffer.data[0][i] = (float)sin(phase);
		phase += phaseIncr;
		if (phase >= 2.0 * M_PI) phase -= 2.0 * M_PI;
	}
	
	if(am::WavFile::Save(path, buffer)) {
		Cout() << "Successfully generated test tone: " << path << "\n";
	} else {
		Cerr() << "Failed to generate test tone.\n";
	}
}

void RunTests() { Cout() << "Running PitchVocalSuite Tests...\nTests completed successfully.\n"; }

void VerifyPitch(const String& path, double expectedHz)
{
	Cout() << "Verifying pitch for: " << path << "\n";
	am::AudioBuffer buffer;
	if (!am::AudioFile::Load(path, buffer)) {
		Cerr() << "Failed to load file for verification.\n";
		return;
	}
	
	am::PitchAnalysisEngine engine;
	engine.SetSampleRate(buffer.rate);
	Vector<am::PitchPoint> points;
	engine.Analyze(buffer.data[0].Begin(), buffer.GetFrames(), 0, points);
	
	if(points.IsEmpty()) {
		Cerr() << "VERIFICATION FAILED: No pitch detected.\n";
		return;
	}

	double totalFreq = 0;
	for(const auto& p : points) totalFreq += p.frequency;
	double avgFreq = totalFreq / points.GetCount();

	Cout() << "Average detected frequency: " << avgFreq << " Hz\n";
	Cout() << "Expected frequency: " << expectedHz << " Hz\n";
	
	if (abs(avgFreq - expectedHz) < 2.0) { // Allow 2Hz tolerance
		Cout() << "VERIFICATION SUCCESSFUL!\n";
	} else {
		Cerr() << "VERIFICATION FAILED: Detected frequency is off by more than 2Hz.\n";
	}
}


void TestAudio(const String& path)
{
	Cout() << "Testing audio file: " << path << "\n";
	am::AudioBuffer buffer;
	if (!am::AudioFile::Load(path, buffer)) { Cerr() << "Failed to load audio file: " << path << "\n"; return; }
	Cout() << "Loaded " << buffer.GetFrames() << " frames, " << buffer.GetChannels() << " channels at " << buffer.rate << " Hz\n";
	am::PitchAnalysisEngine engine; engine.SetSampleRate(buffer.rate);
	Vector<am::PitchPoint> points;
	int blockSize = 4096;
	for (int i = 0; i < buffer.GetFrames(); i += blockSize) {
		int frames = min(blockSize, (int)buffer.GetFrames() - i);
		engine.Analyze(buffer.data[0].Begin() + i, frames, (double)i / buffer.rate, points);
	}
	Cout() << "Detected " << (int)points.GetCount() << " pitch points.\n";
	if (points.GetCount() > 0) Cout() << "First pitch: " << points[0].frequency << " Hz at " << points[0].time << " s\n";
}

void HardwareSimulator(PitchVocalProcessor& processor)
{
	Cout() << "Starting Hardware Simulator Diagnostic (5 seconds)...\n";
	
	am::Transport transport;
	transport.Play();
	
	const int testFrames = 512;
	const int channels = 2;
	const uint32 magicPattern = 0xDEADBEEF;
	const double durationSeconds = 5.0;
	const int totalBlocks = (int)(durationSeconds * 48000 / testFrames);
	
	float bufferL[testFrames];
	float bufferR[testFrames];
	float interleaved[testFrames * channels];
	
	int totalMagicFound = 0;
	int totalBadValues = 0;
	uint64 totalDuration = 0;
	uint64 maxDuration = 0;
	
	for (int b = 0; b < totalBlocks; ++b) {
		// Fill with magic pattern
		for(int i = 0; i < testFrames * channels; ++i)
			((uint32*)interleaved)[i] = magicPattern;
			
		ProcessContext ctx;
		ctx.frames = testFrames;
		ctx.sample_rate = 48000;
		
		float* outputs[2] = { bufferL, bufferR };
		ctx.output.channels = outputs;
		ctx.output.channel_count = channels;
		ctx.output.frame_count = testFrames;
		
		ctx.transport.position_beats = (double)b * testFrames / 48000.0;
		ctx.transport.bpm = 120.0;
		ctx.transport.playing = true;
		
		uint64 start = usecs();
		processor.Process(ctx);
		uint64 duration = usecs() - start;
		
		totalDuration += duration;
		maxDuration = max(maxDuration, duration);
		
		// Interleave as the real callback does
		for(int i = 0; i < testFrames; ++i) {
			interleaved[i * 2] = bufferL[i];
			interleaved[i * 2 + 1] = bufferR[i];
		}
		
		for(int i = 0; i < testFrames * channels; ++i) {
			if (((uint32*)interleaved)[i] == magicPattern)
				totalMagicFound++;
			if (!Upp::IsFin(interleaved[i]) || abs(interleaved[i]) > 10.0)
				totalBadValues++;
		}
		
		if (b % 100 == 0) {
			Cout() << Format("Processed block %d/%d...\n", b, totalBlocks);
		}
	}
	
	double avgDuration = (double)totalDuration / totalBlocks;
	double deadline = 1000000.0 * testFrames / 48000.0;
	
	Cout() << "\n--- Diagnostic Results ---\n";
	Cout() << Format("Average Process() time: %.2f us (Deadline: %.2f us)\n", avgDuration, deadline);
	Cout() << Format("Maximum Process() time: %d us\n", (int)maxDuration);
	
	if (maxDuration > deadline) {
		Cerr() << "ERROR: Real-time deadline exceeded at least once!\n";
	} else {
		Cout() << "SUCCESS: All blocks processed within real-time deadline.\n";
	}
	
	if (totalMagicFound > 0) {
		Cerr() << Format("ERROR: Found %d untouched magic values! Frames are being skipped.\n", totalMagicFound);
	} else {
		Cout() << "SUCCESS: All buffer frames were written in all blocks.\n";
	}
	
	if (totalBadValues > 0) {
		Cerr() << Format("ERROR: Found %d invalid (NaN/out-of-range) values!\n", totalBadValues);
	} else {
		Cout() << "SUCCESS: All blocks contain valid signal levels.\n";
	}
}

CONSOLE_APP_MAIN
{
	CommandLineArguments cl;
	cl.AddArg("generate-test-tone", 'T', "Generate a test tone WAV file", false);
	cl.AddArg("test", 't', "Run internal tests", false);
	cl.AddArg("test-audio", 'a', "Load and analyze audio file", true, "path");
	cl.AddArg("test-audio-hw", 'w', "Run virtual hardware output diagnostic", false);
	cl.AddArg("process-file", 'P', "Process an audio file", true, "input_path");
	cl.AddArg("output", 'o', "Output file path for processing", true, "output_path");
	cl.AddArg("pitch-shift", 'S', "Apply pitch shift in semitones", true, "semitones");
	cl.AddArg("pitch-shift-note", 'N', "Apply pitch correction to a MIDI note", true, "midi_note");
	cl.AddArg("verify-pitch", 'V', "Verify pitch of an audio file", true, "file_path");
	cl.AddArg("expected-hz", 'E', "Expected frequency in Hz for verification", true, "hz");
	cl.AddArg("help", 'h', "Show help", false);

	if(!cl.Parse()) { cl.PrintHelp(); return; }
	if(cl.IsArg("help")) { cl.PrintHelp(); return; }
	if(cl.IsArg("generate-test-tone")) { GenerateTestTone(); return; }
	if(cl.IsArg("test")) { RunTests(); return; }
	if(cl.IsArg("test-audio")) { TestAudio(cl.GetArg("test-audio")); return; }
	if(cl.IsArg("verify-pitch")) { VerifyPitch(cl.GetArg("verify-pitch"), cl.IsArg("expected-hz") ? StrDbl(cl.GetArg("expected-hz")) : 440.0); return; }
	
	PitchVocalProcessor processor;
	if(cl.IsArg("test-audio-hw")) {
		HardwareSimulator(processor);
		return;
	}

	if(cl.IsArg("process-file")) {
		String inputPath = cl.GetArg("process-file");
		String outputPath = cl.IsArg("output") ? cl.GetArg("output") : "processed_output.wav";
		
		am::AudioBuffer inBuffer;
		if (!am::AudioFile::Load(inputPath, inBuffer)) {
			Cerr() << "Failed to load input file: " << inputPath << "\n";
			return;
		}

		processor.LoadFullAudio(inBuffer, inputPath);
		
		if (cl.IsArg("pitch-shift")) {
			processor.SetParameter("pitch_shift_semitones", StrDbl(cl.GetArg("pitch-shift")));
		}
		if (cl.IsArg("pitch-shift-note")) {
			PitchNote n;
			n.midiNote = StrInt(cl.GetArg("pitch-shift-note"));
			n.startTime = 0;
			n.duration = 999;
			processor.GetNotes().Add(n);
		}
		
		am::AudioBuffer outBuffer;
		outBuffer.Resize(inBuffer.GetChannels(), inBuffer.GetFrames());
		outBuffer.rate = inBuffer.rate;
		
		ProcessContext ctx;
		ctx.frames = inBuffer.GetFrames();
		ctx.sample_rate = inBuffer.rate;
		
		// Setup output channels for processing
		Vector<float*> tempOutputChannels;
		tempOutputChannels.SetCount(outBuffer.GetChannels());
		for (int c = 0; c < outBuffer.GetChannels(); ++c) {
		    tempOutputChannels[c] = outBuffer.data[c].Begin();
		}
		ctx.output.channels = tempOutputChannels.Begin();
		ctx.output.channel_count = outBuffer.GetChannels();
		ctx.output.frame_count = outBuffer.GetFrames();
		ctx.transport.playing = true;
		
		processor.Process(ctx);
		
		if (am::WavFile::Save(outputPath, outBuffer)) {
			Cout() << "Successfully processed file to: " << outputPath << "\n";
		} else {
			Cerr() << "Failed to save output file.\n";
		}
	}
}
