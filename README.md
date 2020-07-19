# cpp_canonical_wav_decoder

Simple, minimalistic lib to decode canonical WAV files.

Canonical here means basic WAV files with a main "RIFF" chunk containing a format sub chunk and a data subchunk as described in [this website](https://web.archive.org/web/20190902171853/soundfile.sapp.org/doc/WaveFormat/). Those files are supposed to contain raw audio data in the PCM format, thus having no compression whatsoever.

## How to include in a cmake project

Add this project as submodule in some reserved directory :

```bash
mkdir libs
cd libs
git submodule add git@github.com:soundhive/cpp-canonical-wav-decoder.git
```

Add this lib's `CMakeLists.txt` directory, as well as the headers' ones to your `CMakeLists.txt`, using

```cmake
# Add and link this projetct to yours
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/cpp-canonical-wav-decoder")
target_link_libraries(${PROJECT_NAME} cpp_canonical_wav_decoder)

# Add the headers to your project so that you can import them.
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/cpp-canonical-wav-decoder/include")
```

## How to use

Use the "decode" method taking a file path as argument. You then get a struct containing informations about the audio file.
Do not forget checking for the `is_valid` field. If it is set to false, the library could not read your file and the data of the struct is UB.

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

        std::cout << "File is not a valid canonical WAV file." << std::endl;

    }

    return 0;
}
```

Structure `audio_data` :

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

[project including this](https://github.com/soundhive/cpp-fingerprint-generator)

[Similar project but for MP3 files](https://github.com/lieff/minimp3)
