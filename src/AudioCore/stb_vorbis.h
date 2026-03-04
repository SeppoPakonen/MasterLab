#ifndef STB_VORBIS_H_CUSTOM
#define STB_VORBIS_H_CUSTOM

// Public API declarations for stb_vorbis.
// This file only contains declarations.
// The implementation will be in a separate .cpp file.

#ifdef __cplusplus
extern "C" {
#endif

#ifndef STB_VORBIS_NO_STDIO
#include <stdio.h>
#endif

#ifndef STB_VORBIS_NO_INTTYPES
#include <stdarg.h> // For va_list
#include <stddef.h> // For size_t
#include <stdint.h>
#else
typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
typedef unsigned int uint32;
typedef signed int int32;
typedef unsigned long long uint64;
typedef signed long long int64;
#endif

#if defined(__SIZEOF_INT128__) || defined(_MSC_VER)
#define STB_VORBIS_64BIT_WORDS
#endif

typedef struct stb_vorbis stb_vorbis;

enum STBVorbisError {
    VORBIS_NO_ERROR = 0,
    VORBIS_INVALID_HEAD = 1,
    VORBIS_BAD_PACKET = 2,
    VORBIS_OUT_OF_MEMORY = 3,
    VORBIS_FEATURE_NOT_SUPPORTED = 4,
    VORBIS_NEED_MORE_DATA = 5,
    VORBIS_EOF = 6,
    VORBIS_UNEXPECTED_EOF = 7,
};

#define STB_VORBIS_DECL extern
STB_VORBIS_DECL int stb_vorbis_get_channels(stb_vorbis *vorbis);
STB_VORBIS_DECL int stb_vorbis_get_sample_rate(stb_vorbis *vorbis);
STB_VORBIS_DECL int stb_vorbis_get_samples(stb_vorbis *vorbis);
STB_VORBIS_DECL float stb_vorbis_get_seconds_total(stb_vorbis *vorbis);
STB_VORBIS_DECL float stb_vorbis_get_seconds(stb_vorbis *vorbis);
STB_VORBIS_DECL int stb_vorbis_get_sample_offset(stb_vorbis *vorbis);
STB_VORBIS_DECL int stb_vorbis_is_vorbis(unsigned char *data, int data_len);

STB_VORBIS_DECL float *stb_vorbis_decode_memory(unsigned char *mem, int len, int *channels, int *sample_rate, int *samples_len, STBVorbisError *error);
STB_VORBIS_DECL float *stb_vorbis_decode_callbacks(void *alloc, void *callbacks, void *user_data, int *channels, int *sample_rate, int *samples_len, STBVorbisError *error);
#ifndef STB_VORBIS_NO_STDIO
STB_VORBIS_DECL float *stb_vorbis_decode_filename(const char *filename, int *channels, int *sample_rate, int *samples_len, STBVorbisError *error);
#endif

STB_VORBIS_DECL stb_vorbis *stb_vorbis_open_callbacks(void *alloc, void *callbacks, void *user_data, STBVorbisError *error);
#ifndef STB_VORBIS_NO_STDIO
STB_VORBIS_DECL stb_vorbis *stb_vorbis_open_filename(const char *filename, STBVorbisError *error);
#endif
STB_VORBIS_DECL stb_vorbis *stb_vorbis_open_memory(unsigned char *mem, int len, STBVorbisError *error);

STB_VORBIS_DECL int stb_vorbis_get_frame_float(stb_vorbis *vorbis, int *channels, float ***output);
STB_VORBIS_DECL int stb_vorbis_get_frame_float_ex(stb_vorbis *vorbis, int *channels, float ***output, int *start_offset, int *end_offset);

STB_VORBIS_DECL int stb_vorbis_seek(stb_vorbis *vorbis, int sample_number);
STB_VORBIS_DECL int stb_vorbis_seek_float(stb_vorbis *vorbis, float sample_number);

STB_VORBIS_DECL void stb_vorbis_close(stb_vorbis *vorbis);

// stb_vorbis_info is defined in the .h file
typedef struct stb_vorbis_info
{
   unsigned int sample_rate;
   int channels;
   unsigned int setup_memory_required;
   unsigned int setup_temp_memory_required;
   unsigned int temp_memory_required;
   int max_frame_size;
} stb_vorbis_info;

#ifdef __cplusplus
}
#endif

#endif // STB_VORBIS_H_CUSTOM