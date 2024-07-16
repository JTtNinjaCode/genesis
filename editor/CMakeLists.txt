cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
project(editor VERSION 0.1.0)

#force to use c++ 17, or failed to build
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(editor ${SRC})

#source files
file(GLOB_RECURSE SOURCES "./**/*.cc")

#header files
file(GLOB_RECURSE HEADERS "./**/*.h")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

# add macro
add_compile_definitions(
    GLM_ENABLE_EXPERIMENTAL

    _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING
	_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS
)

target_sources(editor
    PRIVATE
    source.cc
    ${HEADERS}
    ${SOURCES}
)

target_compile_options(editor PRIVATE /WX)
target_link_libraries(editor PRIVATE genesis imgui -WHOLEARCHIVE:$<TARGET_FILE:genesis>)
target_include_directories(editor PRIVATE .)

#include imgui
set(IMGUI_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/third_party/imgui)
target_include_directories(genesis PUBLIC  ${IMGUI_INCLUDE_DIRS})

#include imgui backends
set(IMGUI_BACKENDS_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/third_party/imgui/backends)
target_include_directories(genesis PUBLIC  ${IMGUI_BACKENDS_INCLUDE_DIRS})