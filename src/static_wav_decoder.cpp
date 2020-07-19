#include <static_wav_decoder.hpp>
#include <cstring>
#include <generic.hpp>

namespace wd = wav_decoder;
namespace fs = std::experimental::filesystem;
namespace gf = generic_funcs;

std::shared_ptr<wd::audio_data> wd::decode(const std::string &path_to_file)
{
    //check for null.
    if (!fs::exists(path_to_file) || fs::is_directory(path_to_file))
    {
        throw is_not_file_exception();
    }

    //define size and open stream.
    size_t file_size = fs::file_size(path_to_file);
    std::ifstream source_file(path_to_file, std::ios::binary);

    //Buffer containing the file, signed char because needed for the function "read"
    char *temp_file_buffer = new char[file_size + 1];

    //Read the whole file into a buffer
    source_file.read(temp_file_buffer, file_size);

    //cast to unsigned char to be able to read it
    unsigned char *buffer = reinterpret_cast<unsigned char *>(temp_file_buffer);
    

    std::shared_ptr<wd::audio_data> data = parse_file(buffer, file_size);

    delete[](buffer);

    return data;
}

std::shared_ptr<char> wd::cpy_audio_buffer(unsigned char *buffer, const size_t &buffer_size)
{
    char *new_buffer = new char[buffer_size + 1];

    memcpy(new_buffer, buffer, buffer_size);

    return std::shared_ptr<char>(new_buffer, std::default_delete<char[]>());
}

// std::string wd::extract_audio_format(unsigned char *buffer) {

//     return gf::bin_to_string(buffer + AUDIOFORMAT_START, buffer + AUDIOFORMAT_END);
// }

std::shared_ptr<wd::audio_data> wd::parse_file(unsigned char *buffer, size_t buffer_size) {


    std::unique_ptr<wd::audio_data> data = std::make_unique<wd::audio_data>();

    //main chunk
    std::string     main_chunk_id       = gf::bin_to_string(buffer, buffer + MAIN_CHUNK_ID_END);
    size_t          main_chunk_size     = gf::bin_to_number<size_t>(buffer + MAIN_CHUNK_SIZE_START, buffer + MAIN_CHUNK_SIZE_END);
    std::string     main_chunk_format   = gf::bin_to_string(buffer + MAIN_CHUNK_FORMAT_START, buffer + MAIN_CHUNK_FORMAT_END);

    //first subchunk
    std::string     info_chunk_id       = gf::bin_to_string(buffer + INFO_CHUNK_ID_START, buffer + INFO_CHUNK_ID_END);
    size_t          info_chunk_size     = gf::bin_to_number<size_t>(buffer + INFO_CHUNK_SIZE_START, buffer + INFO_CHUNK_SIZE_START);
    unsigned int    info_chunk_format   = gf::bin_to_number<unsigned int>(buffer + INFO_CHUNK_FORMAT_START, buffer + INFO_CHUNK_FORMAT_START);
    unsigned int    channels            = gf::bin_to_number<unsigned int>(buffer + INFO_CHUNK_CHANNELS_START, buffer + INFO_CHUNK_CHANNELS_END);
    unsigned int    sr                  = gf::bin_to_number<unsigned int>(buffer + INFO_CHUNK_SR_START, buffer + INFO_CHUNK_SR_END);
    unsigned int    byterate            = gf::bin_to_number<unsigned int>(buffer + INFO_CHUNK_BYTERATE_START, buffer + INFO_CHUNK_BYTERATE_END);
    size_t          block_align         = gf::bin_to_number<size_t>(buffer + INFO_CHUNK_BLOCK_ALIGN_START, buffer + INFO_CHUNK_BLOCK_ALIGN_END);
    size_t          bps                 = gf::bin_to_number<size_t>(buffer + INFO_CHUNK_BPS_START, buffer + INFO_CHUNK_BPS_END);

    //second subchunk
    std::string     audio_chunk_id      = gf::bin_to_string(buffer + AUDIO_CHUNK_ID_START, buffer + AUDIO_CHUNK_ID_END);
    size_t          audio_chunk_size    = gf::bin_to_number<size_t>(buffer + AUDIO_CHUNK_SIZE_START, buffer + AUDIO_CHUNK_SIZE_END);


    if (main_chunk_id != "RIFF"     ||
        main_chunk_format != "WAVE" ||
        info_chunk_id != "fmt "     ||
        info_chunk_format != 1      ||
        audio_chunk_id != "data") {
            data->is_valid = false;
        }
    else {
        data->is_valid = true;

        // if audio format is 1, then format is PCM.
        data->audio_format = "PCM";

        data->nb_channels = channels;
        data->byte_rate = byterate;
        data->sample_rate = sr;
        data->block_align = block_align;
        data->bits_per_sample = bps;
        data->buffer_length = audio_chunk_size;
        data->audio_buffer =  cpy_audio_buffer(buffer + AUDIO_CHUNK_DATA_START, audio_chunk_size);
    }

    


    return data;
}

