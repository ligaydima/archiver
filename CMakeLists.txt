cmake_minimum_required(VERSION 3.0)

project(archiver CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif (NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall -Werror=return-type")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
add_subdirectory(Google_tests)
add_executable(archiver
        heap.h node.h trie.h datareader.h datawriter.h
        main.cpp heap.cpp node.cpp trie.cpp datareader.cpp datawriter.cpp encoder.cpp encoder.h argumentparser.cpp argumentparser.h archiver.cpp archiver.h unarchiver.cpp unarchiver.h)


