#include <wav_file.hpp>

namespace fs = std::experimental::filesystem;

wav_file::wav_file(const std::string &path_to_file)
{
    //check for null
    if (!fs::exists(path_to_file) || fs::is_directory(path_to_file))
    {
        throw new is_not_file_exception;
    }

    //define size and open stream
    int file_size = fs::file_size(path_to_file);
    std::ifstream source_file(path_to_file, std::ios::in);

    //allcoate main chunk header buffer
    char *main_header_buffer = new char[MAIN_CHUNK_SIZE];
    char *info_chunk_buffer = new char[INFO_CHUNK_SIZE];
    char *data_chunk_buffer = new char[file_size];

    //read the file
    source_file.read(main_header_buffer, MAIN_CHUNK_SIZE);
    source_file.read(info_chunk_buffer, INFO_CHUNK_SIZE);
    //audio data chunk is until end of file.
    source_file.read(data_chunk_buffer, file_size);

    //create the structures
    this->m_chunk = new main_chunk(main_header_buffer,
                                   info_chunk_buffer,
                                   data_chunk_buffer);

    source_file.close();
}

bool wav_file::is_valid()
{
    return (this->m_chunk && this->m_chunk->is_valid());
}

audio_data *wav_file::get_audio_data(){
    audio_data *data = new audio_data; 
    data->audio_format = *this->m_chunk->infos()->audio_format();
    data->nb_channels = this->m_chunk->infos()->nb_channels();
    data->byte_rate = this->m_chunk->infos()->byte_rate();
    data->sample_rate = this->m_chunk->infos()->sample_rate();
    data->block_align = this->m_chunk->infos()->block_align();
    data->bits_per_sample = this->m_chunk->infos()->sample_size_bits();
    data->buffer_length = this->m_chunk->audio()->audio_data_length();
    data->audio_buffer = this->m_chunk->audio()->audio_data();
    

}