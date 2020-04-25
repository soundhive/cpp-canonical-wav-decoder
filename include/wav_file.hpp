#include <chunk.hpp>
#include <exception>
#include <string>
#include <fstream>
#include <iostream>
#include <experimental/filesystem>

struct audio_data {

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

    char* get_audio_data();
    
    int decode(char *buffer);
    

    private:

    std::string path;

    main_chunk *m_chunk;

};

