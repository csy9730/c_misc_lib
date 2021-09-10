cmake_minimum_required(VERSION 2.8.4)

project(pXtarDemo)

include_directories ("${PROJECT_SOURCE_DIR}/include")
file(GLOB file_source *.c)
set(source ${file_source})

add_executable(zalxtar "xtar.c")
add_dependencies(zalxtar xtar)
target_link_libraries(zalxtar xtar)

add_executable(zalunxtar "unxtar.c")
add_dependencies(zalunxtar xtar)
target_link_libraries(zalunxtar xtar)

install(TARGETS zalxtar DESTINATION  ${PROJECT_BINARY_DIR}/bin)
install(TARGETS zalunxtar DESTINATION  ${PROJECT_BINARY_DIR}/bin)