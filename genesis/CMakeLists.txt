cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
project(genesis VERSION 0.1.0)

#force to use c++ 17, or failed to build
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(genesis STATIC)

#source files
file(GLOB_RECURSE SOURCES "./**/*.cc")

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
	GENESIS_DEBUG
	GENESIS_ASSERT

	GLM_FORCE_SILENT_WARNINGS
	GLM_ENABLE_EXPERIMENTAL
	GLFW_INCLUDE_NONE

	_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING
	_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS
)

target_compile_options(genesis PRIVATE /WX)
target_link_libraries(genesis PRIVATE glfw glad assimp RTTR::Core_Lib freetype stb fmod fmod_studio)
target_link_libraries(genesis PUBLIC spdlog glm easy_profiler sol2)

#include genesis
set(ENGINE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/genesis)
target_include_directories(genesis PUBLIC ${ENGINE_INCLUDE_DIRS})