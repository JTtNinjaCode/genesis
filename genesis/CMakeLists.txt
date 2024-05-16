cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
project(genesis VERSION 0.1.0)

#force to use c++ 17, or failed to build
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#build static library
add_library(genesis STATIC)

#source files
file(GLOB_RECURSE SOURCES "./**/*.cpp")

#header files
file(GLOB_RECURSE HEADERS "./**/*.h")

target_sources(genesis
    PRIVATE
    genesis.h
    ${HEADERS}
    ${SOURCES}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

#define macro
add_compile_definitions(
	GLFW_INCLUDE_NONE
	GLM_ENABLE_EXPERIMENTAL
	GENESIS_ASSERT
	GLM_FORCE_SILENT_WARNINGS
	GENESIS_DEBUG
)

#link library
target_link_libraries(genesis PRIVATE glfw glad assimp RTTR::Core_Lib freetype)
target_link_libraries(genesis PUBLIC spdlog glm easy_profiler)

#include genesis
set(ENGINE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/genesis)
target_include_directories(genesis PUBLIC ${ENGINE_INCLUDE_DIRS})

#include stb
set(STB_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/third_party/stb)
target_include_directories(genesis PRIVATE ${STB_INCLUDE_DIRS})