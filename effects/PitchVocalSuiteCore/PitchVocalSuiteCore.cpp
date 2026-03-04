#include "PitchVocalSuiteCore.h"
#include <AudioCore/AudioFile.h>

PitchVocalProcessor::PitchVocalProcessor()
{
	PluginSDK::ParameterDescriptor pPitchShift;
	pPitchShift.id = "pitch_shift_semitones";
	pPitchShift.name = "Pitch Shift (Semitones)";
	pPitchShift.min = -12.0;
	pPitchShift.max = 12.0;
	pPitchShift.default_value = 0.0;
	Parameters().Add(pPitchShift);
}

String PitchVocalProcessor::GetCachePath(const String& path)
{
	String cacheDir = AppendFileName(GetHomeDirectory(), ".masterlab/cache/pitch-vocal-editor");
	RealizeDirectory(cacheDir);
	
	Md5Stream hash;
	hash.Put(path);
	hash.Put64(GetFileLength(path));
	
	FileTime ft = GetFileTime(path);
	hash.Put(&ft, sizeof(ft));
	
	return AppendFileName(cacheDir, hash.FinishString());
}

void PitchVocalProcessor::LoadFullAudio(const am::AudioBuffer& buffer, const String& path)
{
	fullWaveform.Clear();
	pitchPoints.Clear();
	
	if (buffer.GetFrames() == 0) return;
	
	fullAudioBuffer.Resize(buffer.GetChannels(), buffer.GetFrames());
	fullAudioBuffer.rate = buffer.rate;
	for(int c = 0; c < buffer.GetChannels(); ++c) {
		for(int i = 0; i < buffer.GetFrames(); ++i) {
			fullAudioBuffer.data[c][i] = buffer.data[c][i];
		}
	}

	Log(Format("Loading full audio: %d frames", (int)buffer.GetFrames()));
	
	int step = max(1, (int)buffer.GetFrames() / 4000);
	for (int i = 0; i < buffer.GetFrames(); i += step) {
		float maxV = 0;
		for (int j = 0; j < step && i + j < buffer.GetFrames(); ++j) {
			maxV = max(maxV, abs(buffer.data[0][i + j]));
		}
		fullWaveform.Add(maxV);
	}
	
	String cachePath = GetCachePath(path);
	if (FileExists(cachePath)) {
		Log("Loading pitch analysis from cache...");
		String json = LoadFile(cachePath);
		if (!json.IsEmpty()) {
			JsonIO jio(json);
			jio("points", pitchPoints);
			Log(Format("Cache loaded. Found %d pitch points.", (int)pitchPoints.GetCount()));
			return;
		}
	}

	Log("Performing offline pitch analysis (this may take a while)...");
	pitchEngine.SetSampleRate(buffer.rate);
	int blockSize = 4096;
	for (int i = 0; i < buffer.GetFrames(); i += blockSize) {
		int frames = min(blockSize, (int)buffer.GetFrames() - i);
		pitchEngine.Analyze(buffer.data[0].Begin() + i, frames, (double)i / buffer.rate, pitchPoints);
	}
	
	Log(Format("Analysis complete. Detected %d pitch points.", (int)pitchPoints.GetCount()));
	
	ValueMap m;
	m.Add("points", StoreAsJsonValue(pitchPoints));
	SaveFile(cachePath, m.ToString());
}

void PitchVocalProcessor::Process(PluginSDK::ProcessContext& ctx)
{
	pitch_shift_semitones = GetParameter("pitch_shift_semitones");
	double pitchShiftRatio = pow(2.0, pitch_shift_semitones / 12.0);

	int64 totalFrames = fullAudioBuffer.GetFrames();
	int channels = fullAudioBuffer.GetChannels();
	
	if (totalFrames > 0 && channels > 0) {
		am::AudioBuffer tempBuffer;
		tempBuffer.Resize(ctx.output.channel_count, ctx.frames);
		
		int64 startFrame = (int64)(ctx.transport.position_beats * fullAudioBuffer.rate);
		for (int i = 0; i < ctx.frames; ++i) {
			int64 frame = startFrame + i;
			for (int c = 0; c < ctx.output.channel_count; ++c) {
				if (frame >= 0 && frame < totalFrames) {
					int sourceChannel = c % channels;
					tempBuffer.data[c][i] = fullAudioBuffer.data[sourceChannel][(int)frame];
				} else {
					tempBuffer.data[c][i] = 0;
				}
			}
		}
		
		Vector<double> ratios;
		ratios.Add(pitchShiftRatio);
		phaseVocoder.Process(tempBuffer, ratios);
		
		for (int i = 0; i < ctx.frames; ++i) {
			for (int c = 0; c < ctx.output.channel_count; ++c) {
				ctx.output.GetChannel(c)[i] = tempBuffer.data[c][i];
			}
		}
	} else {
		for (int c = 0; c < ctx.output.channel_count; ++c) {
			float* ch = ctx.output.GetChannel(c);
			for (int i = 0; i < ctx.frames; ++i) ch[i] = 0;
		}
	}
}
