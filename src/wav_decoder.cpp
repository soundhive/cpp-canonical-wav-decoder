#include <wav_decoder.hpp>

namespace fs = std::experimental::filesystem;



namespace wd = wav_decoder;

wd::wav_file::wav_file(const std::string &path_to_file)
{
    //check for null.
    if (!fs::exists(path_to_file) || fs::is_directory(path_to_file))
    {
        throw is_not_file_exception();
    }

    //define size and open stream.
    int file_size = fs::file_size(path_to_file);
    std::ifstream source_file(path_to_file, std::ios::binary);

    //allcoate main chunk header buffer.
    // std::shared_ptr<char> main_header_buffer = std::shared_ptr<char>(new char[MAIN_CHUNK_SIZE]);
    // std::shared_ptr<char> info_chunk_buffer = std::shared_ptr<char>(new char[INFO_CHUNK_SIZE]);
    // std::shared_ptr<char> data_chunk_buffer = std::shared_ptr<char>(new char[file_size - (MAIN_CHUNK_SIZE + INFO_CHUNK_SIZE)]);

    // std::shared_ptr<char> main_chunk_buffer(new char[MAIN_CHUNK_SIZE]);
    // std::shared_ptr<char> info_chunk_buffer(new char[INFO_CHUNK_SIZE], [](char *p) { delete[] p; });
    // std::shared_ptr<char> data_chunk_buffer(new char[file_size - (MAIN_CHUNK_SIZE + INFO_CHUNK_SIZE)], [](char *p) { delete[] p; });


    // std::shared_ptr<char> main_chunk_buffer = std::make_shared<char>(MAIN_CHUNK_SIZE);
    // std::shared_ptr<char> info_chunk_buffer = std::make_shared<char>(INFO_CHUNK_SIZE);
    // std::shared_ptr<char> data_chunk_buffer = std::make_shared<char>(file_size));



    //Buffer containing the file
    char* raw_file_buffer =new char[file_size];

    //read the file.
    // source_file.read(main_header_buffer, MAIN_CHUNK_SIZE);
    // source_file.read(info_chunk_buffer, INFO_CHUNK_SIZE);

    //audio data chunk is until end of file.
    source_file.read(raw_file_buffer, file_size);


    std::shared_ptr<unsigned char> file_buffer = std::make_shared<unsigned char>(file_size);

    //create the structures
    this->m_chunk = new wcd::main_chunk(&file_buffer);
    source_file.close();
}

wd::wav_file::~wav_file() {
    delete(this->m_chunk);
}


//Returns false if file is not recognized as cannonical wave.
bool wd::wav_file::is_valid()
{
    return (this->m_chunk && this->m_chunk->is_valid());
}

//Returns the audio data structure filled with informations.
std::unique_ptr<wd::audio_data >wd::wav_file::get_audio_data()
{
    std::unique_ptr<wd::audio_data> data = std::make_unique<wd::audio_data>();
    data->audio_format = *this->m_chunk->infos()->audio_format();
    data->nb_channels = this->m_chunk->infos()->nb_channels();
    data->byte_rate = this->m_chunk->infos()->byte_rate();
    data->sample_rate = this->m_chunk->infos()->sample_rate();
    data->block_align = this->m_chunk->infos()->block_align();
    data->bits_per_sample = this->m_chunk->infos()->sample_size_bits();
    data->buffer_length = this->m_chunk->audio()->audio_data_length(); 
    unsigned char * buffer = this->m_chunk->audio()->cpy_audio_data();
    data->audio_buffer = std::make_unique<unsigned char>(*buffer);
    return data;
}




