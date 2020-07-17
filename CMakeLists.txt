#./CMakeLists.txt
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

project(cpp_cannonical_wav_decoder
    VERSION "0.0.2"
    DESCRIPTION "cpp_cannonical_wav_decoder"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
link_libraries(stdc++fs)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} ${SOURCES})

set(INCLUDES 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)



target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})





