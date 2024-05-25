cmake_minimum_required(VERSION 3.10)

project(URL_parser_debugger)

# source files
aux_source_directory(./src SOURCES)

# include directories
include_directories(./include)

# executable target
add_executable(URL_parser_debugger ${SOURCES})