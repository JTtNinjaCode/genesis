cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(genesis)

add_subdirectory(third_party)

add_subdirectory(genesis)
target_compile_options(genesis PUBLIC /wd4819)

add_subdirectory(sandbox)
target_compile_options(sandbox PUBLIC /wd4819)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT sandbox)