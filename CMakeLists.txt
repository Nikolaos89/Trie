cmake_minimum_required(VERSION 3.15)
project(Trie)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(cmake-build-debug)

add_executable(Trie
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/Trie.h
        main.cpp Trie.h)
