# cpp_cannonical_wav_decoder
Simple, minimalistic lib to decode cannonical Wav files. 

Cannonical here means basic wav files  with a main "RIFF" chunk containing a format sub chunk and a data subchink as described in [this website](https://web.archive.org/web/20190902171853/soundfile.sapp.org/doc/WaveFormat/). Those files are supposed to contain raw audio data in the PCM format, thus having no compression whatsoever.

## How to include in a cmake project
Add `CMakeLists.txt` directory to your `CMakeLists.txt`, using 
```cmake
 add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/cpp_cannonical_wav_decoder")
 ```


## How to use
Use the "decode" method using a file path. You then get a struct containing informations about the audio file.
Do not forget checking for the `is_valid` field. If it is set to false, the library could not read your file and the datas of the struct are UB.

Example of use : 
```c++
#include <wav_file.hpp>

int main(int argc, char const *argv[])
{
    std::shared_ptr<wd::audio_data> data  = wd::decode(path);
    
    if (data->is_valid) {
        std::cout << data->audio_format << std::endl;
        std::cout << data->nb_channels << std::endl;
        std::cout << data->byte_rate << std::endl;
        std::cout << data->sample_rate << std::endl;
        std::cout << data->block_align << std::endl;
        std::cout << data->bits_per_sample << std::endl;
        std::cout << data->buffer_length << std::endl;
    }
    else {

        std::cout << "File is not a valid cannonical WAV file." << std::endl;
    
    }

    return 0;
}
```

Structure ``audio_data`` :
```c++
struct audio_data
    {
        bool is_valid;
        std::string audio_format;
        int nb_channels;
        int byte_rate;
        int sample_rate;
        int block_align;
        int bits_per_sample;
        size_t buffer_length;
        std::shared_ptr<unsigned char> audio_buffer;
    };
```

## Other

I will keep track of my research concerning this project on [this document](https://docs.google.com/document/d/1LdD37KP_V9XN9EcEkLolgNTQBt_bSdWRyXJFRHddspM)

[Similar project but for MP3 files](https://github.com/lieff/minimp3)