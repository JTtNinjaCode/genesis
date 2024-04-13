cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
project(genesis VERSION 0.1.0)

#force to use c++ 17, or failed to build
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#build static library
add_library(genesis STATIC)

#source files
set(SOURCES
    genesis.h
    core/application.cpp
    core/imgui/imgui_layer.cpp
    core/input.cpp
    core/layer/layer.cpp
    core/layer/layer_stack.cpp
    core/log/log.cpp
    core/math_struct.cpp
    core/profile/profile_timer.cpp
    core/renderer/buffer.cpp
    core/renderer/buffer_layout.cpp
    core/renderer/camera/orthographic_camera.cpp
    core/renderer/camera/orthographic_camera_controller.cpp
    core/renderer/camera/perspective_camera.cpp
    core/renderer/camera/perspective_camera_controller.cpp
    core/renderer/graphic_context.cpp
    core/renderer/renderer_3d.cpp
    core/renderer/renderer_2d.cpp
    core/renderer/renderer_api.cpp
    core/renderer/render_command.cpp
    core/renderer/shader.cpp
    core/renderer/shader_library.cpp
    core/renderer/texture.cpp
    core/renderer/vertex_array.cpp
    core/renderer/mesh.cpp
    core/renderer/model.cpp
    core/timer.cpp
    core/time_step.cpp
    core/window.cpp
    platform/input/glfw_input.cpp
    platform/render_api/opengl/opengl_buffer.cpp
    platform/render_api/opengl/opengl_context.cpp
    platform/render_api/opengl/opengl_render_command.cpp
    platform/render_api/opengl/opengl_shader.cpp
    platform/render_api/opengl/opengl_texture.cpp
    platform/render_api/opengl/opengl_vertex_array.cpp
    platform/window/glfw_window.cpp
    resource/opengl_texture_compressor.cpp
)

#header files
set(HEADERS
    core/application.h
    core/core.h
    core/entry_point.h
    core/input.h
    core/math_struct.h
    core/timer.h
    core/time_step.h
    core/window.h
    core/events/event.h
    core/events/key_event.h
    core/events/mouse_event.h
    core/events/window_event.h
    core/imgui/imgui_layer.h
    core/layer/layer.h
    core/layer/layer_stack.h
    core/log/log.h
    core/profile/profile_timer.h
    core/renderer/buffer.h
    core/renderer/buffer_layout.h
    core/renderer/graphic_context.h
    core/renderer/renderer_3d.h
    core/renderer/renderer_2d.h
    core/renderer/renderer_api.h
    core/renderer/render_command.h
    core/renderer/shader.h
    core/renderer/shader_library.h
    core/renderer/texture.h
    core/renderer/vertex_array.h
    core/renderer/camera/orthographic_camera.h
    core/renderer/camera/orthographic_camera_controller.h
    core/renderer/camera/perspective_camera.h
    core/renderer/camera/perspective_camera_controller.h
    core/renderer/mesh.h
    core/renderer/model.h
    platform/input/glfw_input.h
    platform/render_api/opengl/opengl_buffer.h
    platform/render_api/opengl/opengl_context.h
    platform/render_api/opengl/opengl_render_command.h
    platform/render_api/opengl/opengl_shader.h
    platform/render_api/opengl/opengl_texture.h
    platform/render_api/opengl/opengl_vertex_array.h
    platform/window/glfw_window.h
    resource/opengl_texture_compressor.h
)

target_sources(genesis
    INTERFACE
    genesis.h

    PRIVATE
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
target_link_libraries(genesis PRIVATE glfw glad assimp)
target_link_libraries(genesis PUBLIC spdlog imgui glm)

#include genesis
set(ENGINE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/genesis)
target_include_directories(genesis PUBLIC ${ENGINE_INCLUDE_DIRS})

#include stb
set(STB_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/third_party/stb)
target_include_directories(genesis PRIVATE ${STB_INCLUDE_DIRS})

#include imgui
set(IMGUI_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/third_party/imgui)
target_include_directories(genesis PUBLIC  ${IMGUI_INCLUDE_DIRS})

#include imgui backends
set(IMGUI_BACKENDS_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/third_party/imgui/backends)
target_include_directories(genesis PUBLIC  ${IMGUI_BACKENDS_INCLUDE_DIRS})
