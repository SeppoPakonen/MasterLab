#include "AudioCore.h"

namespace am {
namespace Audio {

// --- CuteAudioFileFactory ---
CuteAudioFileFactory* CuteAudioFileFactory::instance = nullptr;

CuteAudioFileFactory::CuteAudioFileFactory()
{
	FileFormat wav_format;
	wav_format.type = SndFile;
	wav_format.name = "WAV";
	wav_format.ext = ".wav";
	formats.Add(wav_format);
	types.Add(".wav", wav_format);
	
	FileFormat ogg_format;
	ogg_format.type = VorbisFile;
	ogg_format.name = "OGG";
	ogg_format.ext = ".ogg";
	formats.Add(ogg_format);
	types.Add(".ogg", ogg_format);
	
	FileFormat mp3_format;
	mp3_format.type = MadFile;
	mp3_format.name = "MP3";
	mp3_format.ext = ".mp3";
	formats.Add(mp3_format);
	types.Add(".mp3", mp3_format);
	
	for (int i = 0; i < formats.GetCount(); ++i) {
		filters.Add(formats[i].name + " files (*" + formats[i].ext + ")");
		extensions.Add("*" + formats[i].ext);
	}
}

CuteAudioFileFactory::~CuteAudioFileFactory() {}
CuteAudioFileFactory* CuteAudioFileFactory::GetInstance() { if(!instance) instance = new CuteAudioFileFactory(); return instance; }
const CuteAudioFileFactory::FileFormats& CuteAudioFileFactory::GetFormats() { return GetInstance()->formats; }
const CuteAudioFileFactory::FileTypes& CuteAudioFileFactory::GetTypes() { return GetInstance()->types; }
const Vector<String>& CuteAudioFileFactory::GetFilters() { return GetInstance()->filters; }
const Vector<String>& CuteAudioFileFactory::GetExtensions() { return GetInstance()->extensions; }
void CuteAudioFileFactory::SetDefaultType(const String& ext, int type, int format, int quality) {
	GetInstance()->default_ext = ext;
	GetInstance()->default_type = type;
	GetInstance()->default_format = format;
	GetInstance()->default_quality = quality;
}
String CuteAudioFileFactory::GetDefaultExt() { return GetInstance()->default_ext; }
bool CuteAudioFileFactory::IsValidFormat(const FileFormat* format, int file_format) { return true; }

CuteAudioFile* CuteAudioFileFactory::CreateAudioFile(const String& file_name, unsigned short channels, unsigned int sample_rate, unsigned int buffer_size, int format)
{
	return GetInstance()->NewAudioFile(file_name, channels, sample_rate, buffer_size, format);
}

CuteAudioFile* CuteAudioFileFactory::NewAudioFile(const String& file_name, unsigned short channels, unsigned int sample_rate, unsigned int buffer_size, int format)
{
	String ext = ToLower(GetFileExt(file_name));
	int type = types.Find(ext);
	if (type < 0)
		return nullptr;
		
	switch(types[type].type) {
		case SndFile:    return new CuteAudioSndFile();
		case VorbisFile: return new CuteAudioVorbisFile();
		case MadFile:    return new CuteAudioMadFile();
	}
	return nullptr;
}

int CuteAudioFileFactory::GetDefaultFormat() { return GetInstance()->default_format; }
int CuteAudioFileFactory::GetDefaultQuality() { return GetInstance()->default_quality; }

} // namespace Audio
} // namespace am
