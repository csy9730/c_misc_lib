include_directories ("${PROJECT_SOURCE_DIR}/include")
file(GLOB file_source *.c utils/*.c)
set(source ${file_source})

add_executable(xtarTest ${source})
add_dependencies(xtarTest xtar)
target_link_libraries(xtarTest xtar)