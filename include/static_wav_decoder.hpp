#include <string>
#include <memory> 


namespace wav_decoder {
//Generic chunk properties
#define CHUNK_ID_START 0
#define CHUNK_ID_END 3

#define CHUNK_SIZE_START 4
#define CHUNK_SIZE_END 7

//format data on main chunk
#define FORMAT_START 8
#define FORMAT_END 11

//info chunk properties
#define AUDIOFORMAT_START 8
#define AUDIOFORMAT_END 9

#define NUMCHANNELS_START 10
#define NUMCHANNELS_END 11

#define SAMPLERATE_START 12
#define SAMPLERATE_END 15

#define BYTERATE_START 16
#define BYTERATE_END 19

#define BLOCKALIGN_START 20
#define BLOCKALIGN_END 21

#define BITSPERSAMPLE_START 22
#define BITSPERSAMPLE_END 23

//data
#define AUDIO_DATA_START 8

//size of the header to allocate for the buffers of chunks
#define MAIN_CHUNK_SIZE 12
#define INFO_CHUNK_SIZE 24
//data chunk size is not fixed so we use its start
#define DATA_CHUNK_START 36

#define MAIN_CHUNK_HEADER_SIZE 12

#if !defined(BIG_ENDIAN)
#define BIG_ENDIAN 4321
#endif // BIG_ENDIAN

#if !defined(LITTLE_ENDIAN)
#define LITTLE_ENDIAN 1234
#endif // LITTLE_ENDIAN





struct audio_data
{
    std::string audio_format;
    int nb_channels;
    int byte_rate;
    int sample_rate;
    int block_align;
    int bits_per_sample;
    size_t buffer_length;
    std::unique_ptr<unsigned char> audio_buffer;
};


std::unique_ptr<audio_data> decode(const std::string *path_to_file);





}