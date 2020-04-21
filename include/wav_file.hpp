#include <fstream>
#include <iostream>
#include <exception>



class wav_file {
    public:

    #define CHUNK_ID_SIZE  4;

    wav_file(std::string path_to_file);
    bool is_valid();

    int channels();
    int sample_rate();
    int sample_size();
    int audio_data_length();
    char* audio_data();
    int byte_rate();


    
    int open();
    int close();
    

    private:
    wav_file();
    std::string path;
    char* buffer;
    bool is_valid;

    char* chunk_id;
    char* format;
    int chunk_size;

    char* subchunk_info_id;
    int subchunk_info_size;
    int audio_format;
    int channels;
    int sample_rate;
    int byte_rate;
    int whole_sample_size;
    int sample_size_bits;

    char* subchunk_data_ID;
    int subchunk_data_size;
    char* audio_data;



    ~wav_file();
};