cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(genesis)

message(${PROJECT_SOURCE_DIR})
message(${PROJECT_BINARY_DIR})

add_subdirectory(third_party/glfw)
target_compile_options(glfw PUBLIC /wd4819)

add_subdirectory(third_party/spdlog)
target_compile_options(spdlog PUBLIC /wd4819)

add_subdirectory(third_party/glad)
target_compile_options(glad PUBLIC /wd4819)

add_subdirectory(third_party/assimp)
target_compile_options(assimp PUBLIC /wd4819)

add_subdirectory(third_party/glm)

add_subdirectory(genesis)
target_compile_options(genesis PUBLIC /wd4819)

add_subdirectory(sandbox)
target_compile_options(sandbox PUBLIC /wd4819)

add_subdirectory(cmake)
target_compile_options(imgui PUBLIC /wd4819)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT sandbox)

