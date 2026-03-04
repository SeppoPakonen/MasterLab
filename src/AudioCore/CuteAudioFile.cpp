#include "AudioCore.h"

CuteAudioFileFactory* CuteAudioFileFactory::instance = nullptr;

CuteAudioFileFactory::CuteAudioFileFactory() {
    if(!instance)
        instance = this;
    FileFormat wav_format;
    wav_format.type = SndFile;
    wav_format.name = "Wave";
    wav_format.ext = "wav";
    wav_format.data = 0;
    formats.Add(wav_format);
    types.Add(wav_format.ext, wav_format);
    filters.Add("Wave (*.wav)");
    extensions.Add("wav");
    default_ext = "wav";
}

CuteAudioFileFactory::~CuteAudioFileFactory() {
    if(instance == this)
        instance = nullptr;
}

CuteAudioFileFactory* CuteAudioFileFactory::GetInstance() { return instance; }
const CuteAudioFileFactory::FileFormats& CuteAudioFileFactory::GetFormats() { static FileFormats empty; return instance ? instance->formats : empty; }
const CuteAudioFileFactory::FileTypes& CuteAudioFileFactory::GetTypes() { static FileTypes empty; return instance ? instance->types : empty; }
const Vector<String>& CuteAudioFileFactory::GetFilters() { static Vector<String> empty; return instance ? instance->filters : empty; }
const Vector<String>& CuteAudioFileFactory::GetExtensions() { static Vector<String> empty; return instance ? instance->extensions : empty; }
void CuteAudioFileFactory::SetDefaultType(const String& ext, int type, int format, int quality) { if(instance) { instance->default_ext = ext; instance->default_type = type; instance->default_format = format; instance->default_quality = quality; } }
String CuteAudioFileFactory::GetDefaultExt() { return instance ? instance->default_ext : String("wav"); }
bool CuteAudioFileFactory::IsValidFormat(const FileFormat* format, int file_format) { return format && (file_format < 0 || format->data == file_format); }
CuteAudioFile* CuteAudioFileFactory::CreateAudioFile(const String& file_name, unsigned short channels, unsigned int sample_rate, unsigned int buffer_size, int format) { return instance ? instance->NewAudioFile(file_name, channels, sample_rate, buffer_size, format) : nullptr; }
CuteAudioFile* CuteAudioFileFactory::NewAudioFile(const String& file_name, unsigned short channels, unsigned int sample_rate, unsigned int buffer_size, int format) { (void)file_name; (void)channels; (void)sample_rate; (void)buffer_size; (void)format; return nullptr; }
int CuteAudioFileFactory::GetDefaultFormat() { return instance ? instance->default_format : 0; }
int CuteAudioFileFactory::GetDefaultQuality() { return instance ? instance->default_quality : 4; }
