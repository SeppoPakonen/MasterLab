#include "AudioCore.h"

CuteAudioFileFactory* CuteAudioFileFactory::instance = nullptr;

CuteAudioFileFactory::CuteAudioFileFactory() {
	FileFormat wav_format;
	wav_format.type = SndFile;
	wav_format.name = "WAV";
	wav_format.ext = ".wav";
	formats.Add(wav_format);
	types.Add(wav_format.ext, wav_format);

	FileFormat ogg_format;
	ogg_format.type = VorbisFile;
	ogg_format.name = "OGG";
	ogg_format.ext = ".ogg";
	formats.Add(ogg_format);
	types.Add(ogg_format.ext, ogg_format);

	FileFormat mp3_format;
	mp3_format.type = MadFile;
	mp3_format.name = "MP3";
	mp3_format.ext = ".mp3";
	formats.Add(mp3_format);
	types.Add(mp3_format.ext, mp3_format);

	for(int i = 0; i < formats.GetCount(); ++i) {
		const FileFormat& f = formats[i];
		filters.Add(f.name + " files (*" + f.ext + ")");
		extensions.Add("*" + f.ext);
	}
	default_ext = ".wav";
}

CuteAudioFileFactory::~CuteAudioFileFactory() {}

CuteAudioFileFactory* CuteAudioFileFactory::GetInstance() {
	if(!instance)
		instance = new CuteAudioFileFactory();
	return instance;
}

const CuteAudioFileFactory::FileFormats& CuteAudioFileFactory::GetFormats() {
	return GetInstance()->formats;
}

const CuteAudioFileFactory::FileTypes& CuteAudioFileFactory::GetTypes() {
	return GetInstance()->types;
}

const Vector<String>& CuteAudioFileFactory::GetFilters() {
	return GetInstance()->filters;
}

const Vector<String>& CuteAudioFileFactory::GetExtensions() {
	return GetInstance()->extensions;
}

void CuteAudioFileFactory::SetDefaultType(const String& ext, int type, int format, int quality) {
	CuteAudioFileFactory* f = GetInstance();
	f->default_ext = ext;
	f->default_type = type;
	f->default_format = format;
	f->default_quality = quality;
}

String CuteAudioFileFactory::GetDefaultExt() {
	return GetInstance()->default_ext;
}

bool CuteAudioFileFactory::IsValidFormat(const FileFormat* format, int file_format) {
	(void)file_format;
	return format != nullptr;
}

CuteAudioFile* CuteAudioFileFactory::CreateAudioFile(const String& file_name, unsigned short channels, unsigned int sample_rate, unsigned int buffer_size, int format) {
	return GetInstance()->NewAudioFile(file_name, channels, sample_rate, buffer_size, format);
}

CuteAudioFile* CuteAudioFileFactory::NewAudioFile(const String& file_name, unsigned short channels, unsigned int sample_rate, unsigned int buffer_size, int format) {
	(void)channels;
	(void)sample_rate;
	(void)buffer_size;
	(void)format;

	String ext = ToLower(GetFileExt(file_name));
	int pos = types.Find(ext);
	if(pos < 0)
		return nullptr;

	const FileFormat& f = types[pos];
	switch(f.type) {
	case SndFile:
		return new CuteAudioSndFile();
	case VorbisFile:
		return new CuteAudioVorbisFile();
	case MadFile:
		return new CuteAudioMadFile();
	}
	return nullptr;
}

int CuteAudioFileFactory::GetDefaultFormat() {
	return GetInstance()->default_format;
}

int CuteAudioFileFactory::GetDefaultQuality() {
	return GetInstance()->default_quality;
}
