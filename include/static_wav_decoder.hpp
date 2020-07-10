#include <experimental/filesystem>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

namespace wav_decoder
{

#define MAIN_CHUNK_ID_END 3

#define MAIN_CHUNK_SIZE_START 4
#define MAIN_CHUNK_SIZE_END 7

#define MAIN_CHUNK_FORMAT_START 8
#define MAIN_CHUNK_FORMAT_END 11


#define INFO_CHUNK_ID_START 12
#define INFO_CHUNK_ID_END 15

#define INFO_CHUNK_SIZE_START 16
#define INFO_CHUNK_SIZE_END 19

#define INFO_CHUNK_FORMAT_START 20
#define INFO_CHUNK_FORMAT_END 21

#define INFO_CHUNK_CHANNELS_START 22
#define INFO_CHUNK_CHANNELS_END 23

#define INFO_CHUNK_SR_START 24
#define INFO_CHUNK_SR_END 27

#define INFO_CHUNK_BYTERATE_START 28
#define INFO_CHUNK_BYTERATE_END 31

#define INFO_CHUNK_BLOCK_ALIGN_START 32
#define INFO_CHUNK_BLOCK_ALIGN_END 33

#define INFO_CHUNK_BPS_START 34
#define INFO_CHUNK_BPS_END 35


#define AUDIO_CHUNK_ID_START 36
#define AUDIO_CHUNK_ID_END 39

#define AUDIO_CHUNK_SIZE_START 40
#define AUDIO_CHUNK_SIZE_END 43

#define AUDIO_CHUNK_DATA_START 44


#if !defined(BIG_ENDIAN)
#define BIG_ENDIAN 4321
#endif // BIG_ENDIAN

#if !defined(LITTLE_ENDIAN)
#define LITTLE_ENDIAN 1234
#endif // LITTLE_ENDIAN

    class is_not_file_exception : public std::exception
    {
        virtual const char *what() const throw()
        {
            return "The provided path does not lead to a file.";
        }
    };

    struct audio_data
    {
        bool is_valid;
        std::string audio_format;
        int nb_channels;
        int byte_rate;
        int sample_rate;
        int block_align;
        int bits_per_sample;
        size_t buffer_length;
        std::shared_ptr<unsigned char> audio_buffer;
    };

    std::shared_ptr<audio_data> decode(const std::string &path_to_file);

    std::shared_ptr<unsigned char> cpy_audio_buffer(unsigned char *, const size_t &file_size);

    std::string extract_audio_format(unsigned char *buffer);

    std::shared_ptr<audio_data> parse_file(unsigned char *buffer, size_t buffer_size);
} // namespace wav_decoder