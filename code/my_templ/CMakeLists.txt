cmake_minimum_required(VERSION 2.8.4)

project(pXtar)

# alignment source
file(GLOB file_source src/*.c)
set(source ${file_source})

include_directories ("${PROJECT_SOURCE_DIR}/include")

add_library(xtar ${source})
add_subdirectory("demos")
add_subdirectory("tests")