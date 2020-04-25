#include <chunk.hpp>

chunk::chunk(char *buffer)
{
    if (!buffer)
    {
        throw new invalid_buffer_exception;
    }

    this->m_buffer = buffer;

    this->m_chunk_id = char_array_to_string(this->m_buffer,
                                            &this->m_buffer[CHUNK_ID_END]);

    this->m_chunk_size = char_array_to_number(&this->m_buffer[CHUNK_SIZE_START],
                                              &this->m_buffer[CHUNK_SIZE_END]);
}

std::string chunk::chunk_id()
{
    return this->m_chunk_id;
}

size_t chunk::chunk_size()
{
    return this->m_chunk_size;
}

main_chunk::main_chunk(char *main_header_buffer,
                       char *info_chunk_buffer,
                       char *audio_chunk_buffer) : chunk(main_header_buffer)
{

    this->m_infos = new info_chunk(info_chunk_buffer);

    this->m_audio = new audio_chunk(audio_chunk_buffer);

    this->m_format = char_array_to_string(&this->m_buffer[FORMAT_START],
                                          &this->m_buffer[FORMAT_END]);
}

//States if the current buffer loaded file is a valid Wave file
bool main_chunk::is_valid()
{
    return this->m_audio->is_valid() &&
           this->m_infos->is_valid() &&
           (this->m_format == "WAVE") &&
           (this->m_chunk_id == "RIFF");
}

info_chunk::info_chunk(char *buffer) : chunk(buffer)
{
    int format_identifier = char_array_to_number(&this->m_buffer[AUDIOFORMAT_START],
                                                &this->m_buffer[AUDIOFORMAT_END]);
    if (format_identifier == 1) {
        this->m_format = "PCM";
    } else {
        this->m_format = "unknown";
    }

    this->m_nb_channels = char_array_to_number(&this->m_buffer[NUMCHANNELS_START],
                                               &this->m_buffer[NUMCHANNELS_END]);

    this->m_sample_rate = char_array_to_number(&this->m_buffer[SAMPLERATE_START],
                                               &this->m_buffer[SAMPLERATE_START]);

    this->m_byte_rate = char_array_to_number(&this->m_buffer[BYTERATE_START],
                                             &this->m_buffer[BYTERATE_START]);

    this->m_block_align = char_array_to_number(&this->m_buffer[BLOCKALIGN_START],
                                               &this->m_buffer[BLOCKALIGN_END]);

    this->m_sample_size_bits = char_array_to_number(&this->m_buffer[BITSPERSAMPLE_START],
                                                    &this->m_buffer[BITSPERSAMPLE_END]);
}

bool info_chunk::is_valid()
{
    return this->m_buffer  && this->m_chunk_id == "fmt ";
}

audio_chunk::audio_chunk(char *buffer) : chunk(buffer)
{
    this->m_audio_data = &buffer[AUDIO_DATA_START];
}

bool audio_chunk::is_valid()
{
    return this->m_chunk_id == "data";
}