#include <chunk.hpp>
#include <exception>
#include <fstream>
#include <iostream>
#include <experimental/filesystem>
#include <memory>
namespace wcd = wav_chunk_decoder;

namespace wav_decoder
{

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

class is_not_file_exception : public std::exception
{
    virtual const char *what() const throw()
    {
        return "The provided path does not lead to a file.";
    }
};

class wav_file
{
public:
    wav_file(const std::string &path_to_file);
    ~wav_file();
    bool is_valid();
    std::unique_ptr<audio_data> get_audio_data();

private:
    std::string path;
    std::shared_ptr<unsigned char> file_buffer;
    wcd::main_chunk *m_chunk;
};

} // namespace wav_decoder