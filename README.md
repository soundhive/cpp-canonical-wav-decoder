# cpp_cannonical_wav_decoder
Simple, minimalistic lib to decode cannonical Wav files. 

Cannonical here means basic wav files  with a main "RIFF" chunk containing an format sub chunk and a data subchink as described in [this website](https://web.archive.org/web/20190902171853/soundfile.sapp.org/doc/WaveFormat/).

## How to include in a cmake project
Add `CMakeLists.txt` directory to your `CMakeLists.txt`, using 
```cmake
 add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/avcpp")
 ```


## How to use
Create a wav_file object using the constructor that takes a string reference, then use ``get_audio_data``. It will return a structure that holds everything you may need to read the PCM stream.
Example of use : 
```c++
#include <iostream>
#include <wav_file.hpp>


int main(int argc, char const *argv[])
{
    std::string path = argv[1];
    wav_file file(path);
    std::cout << "validity : " << file.is_valid() << std::endl;
    audio_data *data = file.get_audio_data();
    std::cout << "audio format : " << data->audio_format << std::endl;
    std::cout << "nb channels : " << data->nb_channels << std::endl;
    std::cout << "byte rate : " << data->byte_rate << std::endl;
    std::cout << "sample rate : " << data->sample_rate << std::endl;
    std::cout << "block align : " << data->block_align << std::endl;
    std::cout << "bits per sample " << data->bits_per_sample << std::endl;
    std::cout << "buffer length : " << data->buffer_length << std::endl;

    std::cout << "writing to pcm file..." << std::endl;
    std::ofstream out_file("/home/vagahbond/Documents/ESGI/Projet Annuel/cpp_cannonical_wav_decoder/TEMP/raw_out.pcm", std::ios::out);
    out_file.write(data->audio_buffer, data->buffer_length);
    std::cout << "file written !" << std::endl;
    out_file.close();
    
    return 0;

}
```

Structure ``audio_data`` :
```c++
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
```

## To come
Next, I will comment the code of this library and refactor it to give it the shape of a real lib. After adding unit tests, I plan on extending its support to all kinds of WAV file, and eventually create libs of this kinds for some other formats that would need it.

There will also be an example file.

## Other

I will keep track of my research concerning this project on [this document](https://docs.google.com/document/d/1LdD37KP_V9XN9EcEkLolgNTQBt_bSdWRyXJFRHddspM)

[Similar project but for MP3 files](https://github.com/lieff/minimp3)