cmake_minimum_required (VERSION 2.6)
project (Lua)

option(LIB_SHARED "Use staic" OFF)
include_directories ("${PROJECT_SOURCE_DIR}/include")

file(GLOB LUA_SRC          ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB LUA_INC          ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
set (LUA_EXE ${LUA_SRC} main/lua.c)
set (LUAC_EXE ${LUA_SRC} main/luac.c)

if(LIB_SHARED)
    add_library(liblua SHARED ${LUA_SRC}  ${LUA_INC} )
	message("shared")
else()
    add_library(liblua STATIC ${LUA_SRC}  ${LUA_INC} )
	message("static")
endif()


# add the executable
set (EXTRA_LIBS ${EXTRA_LIBS} liblua)
add_executable (lua  ${LUA_EXE}  ${LUA_INC} )
add_dependencies(lua   liblua)
target_link_libraries (lua  ${EXTRA_LIBS})
add_executable (luac  ${LUA_EXE}  ${LUA_INC} )
add_dependencies(luac   liblua)
target_link_libraries (luac  ${EXTRA_LIBS})

install(TARGETS liblua lua luac DESTINATION  ${PROJECT_BINARY_DIR}/bin)




