cmake_minimum_required(VERSION 3.10)

project(URL_parser_debugger)

# source files
set(SOURCES
    src/main.cpp
    src/tested_parser.cpp
    src/random_url.cpp
    src/basic_url.cpp
    src/parsed_url.cpp
)

# include directories
include_directories(
    include
)

# executable target
add_executable(URL_parser_debugger ${SOURCES})