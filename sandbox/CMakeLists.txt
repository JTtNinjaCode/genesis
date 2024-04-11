cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
project(sandbox VERSION 0.1.0)

#force to use c++ 17, or failed to build
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sandbox ${SRC})

#source files
set(SOURCES
    imgui_layer/sandbox_2d.cpp
    imgui_layer/sandbox_3d.cpp
    source.cpp
)

#header files
set(HEADERS
    imgui_layer/sandbox_2d.h
    imgui_layer/sandbox_3d.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

# add macro
add_compile_definitions(
    GLM_ENABLE_EXPERIMENTAL
)

target_sources(sandbox
    PRIVATE
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(sandbox genesis)