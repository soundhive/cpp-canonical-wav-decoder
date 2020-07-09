#include <iostream>
#include <exception>
#include <generic.hpp>
#include <iomanip>
#include <memory>

namespace wav_chunk_decoder
{

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

class invalid_buffer_exception : public std::exception
{
    virtual const char *what() const throw()
    {
        return "The provided buffer is not valid.";
    }
};

/**
 * Abstract class defining generic data in a chunk
 */
class chunk
{
protected:
    chunk(unsigned char *buffer);
    ~chunk();

    unsigned char *m_buffer;
    std::string m_chunk_id;
    size_t m_chunk_size;
    ~chunk();
};

class audio_chunk : chunk
{
public:
    audio_chunk(unsigned char *buffer);
    ~audio_chunk();

    bool is_valid();
    unsigned char *cpy_audio_data();
    size_t audio_data_length();

private:
    char *m_audio_data;
};

class info_chunk : chunk
{
public:
    info_chunk(unsigned char *buffer);
    ~info_chunk();

    bool is_valid();

    unsigned short nb_channels();
    unsigned short sample_size_bits();
    unsigned int sample_rate();
    unsigned int byte_rate();
    unsigned int block_align();
    std::string *audio_format();

private:
    std::string m_audio_format;

    unsigned short m_nb_channels = 0;
    unsigned short m_sample_size_bits = 0;
    unsigned int m_sample_rate = 0;
    unsigned int m_byte_rate = 0;
    unsigned int m_block_align = 0;
};

/**
 * RIFF chunk containing other chunks
 */
class main_chunk : chunk
{
public:
    //constructor
    main_chunk(const std::shared_ptr<unsigned char>* file_buffer);
    ~main_chunk();
    bool is_valid();

    audio_chunk *audio();
    info_chunk *infos();
    std::string *format();

private:
    std::string m_format;
    audio_chunk *m_audio;
    info_chunk *m_infos;
};

} // namespace wav_chunk_decoder