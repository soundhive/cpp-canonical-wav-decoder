#include <chunk.hpp>
#include <exception>
#include <string>
#include <fstream>
#include <iostream>
#include <experimental/filesystem>

struct audio_data {
    std::string audio_format;
    int nb_channels;
    int byte_rate;
    int sample_rate;
    int block_align;
    int bits_per_sample;
    size_t buffer_length;
    char *audio_buffer;
};

class is_not_file_exception : public std::exception
{
    virtual const char *what() const throw()
    {
        return "The provided path does not lead to a file.";
    }
};





class wav_file {
    public:

    wav_file(const std::string &path_to_file);
    wav_file(const char* file_buffer);

    bool is_valid();

    audio_data *get_audio_data();
    
    int decode(char *buffer);
    

    private:

    std::string path;

    main_chunk *m_chunk;

};

