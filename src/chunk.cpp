#include <chunk.hpp>

namespace gf = generic_funcs;

namespace wcd = wav_chunk_decoder;

/**
 * Constructor ssings primary buffer, and parse chunk ID and size
 */
wcd::chunk::chunk(unsigned char *buffer) : m_buffer(buffer)
{
    std::cout << "Chunk constructor" << std::endl;
    if (!buffer)
    {
        throw invalid_buffer_exception();
    }

    this->m_chunk_id = gf::bin_to_string(this->m_buffer,
                                         &this->m_buffer[CHUNK_ID_END]);

    this->m_chunk_size = gf::bin_to_number<size_t>(&this->m_buffer[CHUNK_SIZE_START],
                                                   &this->m_buffer[CHUNK_SIZE_END]);
}

/**
 * Realocate the main buffer
 */
wcd::chunk::~chunk()
{
    std::cout << "Chunk destructor" << std::endl;
    delete this->m_buffer;
}

wcd::audio_chunk::audio_chunk(unsigned char *buffer) : chunk(buffer), m_audio_data(reinterpret_cast<char *>(&buffer[AUDIO_DATA_START]))
{
    std::cout << "audio-chunk constructor constructor" << std::endl;
}

bool wcd::audio_chunk::is_valid()
{
    return this->m_chunk_id == "data";
}

/**
 * Returns a copy of the audio data portion of the buffer
 */
unsigned char *wcd::audio_chunk::cpy_audio_data()
{
    return this->m_buffer; //TODO: add allocation copy instead to prevent loss of the buffer ?
}

size_t wcd::audio_chunk::audio_data_length()
{
    return this->m_chunk_size;
}

wcd::info_chunk::info_chunk(unsigned char *buffer) : chunk(buffer)
{
    unsigned int format_identifier = gf::bin_to_number<unsigned int>(&this->m_buffer[AUDIOFORMAT_START],
                                                                     &this->m_buffer[AUDIOFORMAT_END]);
    if (format_identifier == 1)
    {
        this->m_audio_format = "PCM";
    }
    else
    {
        this->m_audio_format = "unknown";
    }

    this->m_nb_channels = gf::bin_to_number<unsigned short>(&this->m_buffer[NUMCHANNELS_START],
                                                            &this->m_buffer[NUMCHANNELS_END]);

    this->m_sample_size_bits = gf::bin_to_number<unsigned short>(&this->m_buffer[BITSPERSAMPLE_START],
                                                                 &this->m_buffer[BITSPERSAMPLE_END]);

    this->m_sample_rate = gf::bin_to_number<unsigned int>(&this->m_buffer[SAMPLERATE_START],
                                                          &this->m_buffer[SAMPLERATE_END]);

    this->m_byte_rate = gf::bin_to_number<unsigned int>(&this->m_buffer[BYTERATE_START],
                                                        &this->m_buffer[BYTERATE_END]);

    this->m_block_align = gf::bin_to_number<unsigned int>(&this->m_buffer[BLOCKALIGN_START],
                                                          &this->m_buffer[BLOCKALIGN_END]);
}

bool wcd::info_chunk::is_valid()
{
    return this->m_buffer && this->m_chunk_id == "fmt ";
}

unsigned short wcd::info_chunk::nb_channels()
{
    return this->m_nb_channels;
}

unsigned short wcd::info_chunk::sample_size_bits()
{
    return this->m_sample_size_bits;
}

unsigned int wcd::info_chunk::sample_rate()
{
    return this->m_sample_rate;
}

unsigned int wcd::info_chunk::byte_rate()
{
    return this->m_byte_rate;
}

unsigned int wcd::info_chunk::block_align()
{
    return this->m_block_align;
}

std::string *wcd::info_chunk::audio_format()
{
    return &this->m_audio_format;
}

wcd::main_chunk::main_chunk(const std::shared_ptr<unsigned char> *file_buffer)
    : chunk(reinterpret_cast<unsigned char *>(file_buffer->get()))
{

    this->m_infos = new info_chunk(reinterpret_cast<unsigned char*>(file_buffer->get() + MAIN_CHUNK_SIZE));

    this->m_audio = new audio_chunk(reinterpret_cast<unsigned char*>(file_buffer->get() + MAIN_CHUNK_SIZE + INFO_CHUNK_SIZE));

    this->m_format = gf::bin_to_string(&this->m_buffer[FORMAT_START],
                                       &this->m_buffer[FORMAT_END]);
}

//States if the current buffer loaded file is a valid Wave file
bool wcd::main_chunk::is_valid()
{
    return this->m_audio->is_valid() &&
           this->m_infos->is_valid() &&
           (this->m_format == "WAVE") &&
           (this->m_chunk_id == "RIFF");
}

wcd::audio_chunk *wcd::main_chunk::audio()
{
    return this->m_audio;
}

wcd::info_chunk *wcd::main_chunk::infos()
{
    return this->m_infos;
}

std::string *wcd::main_chunk::format()
{
    return &this->m_format;
}
