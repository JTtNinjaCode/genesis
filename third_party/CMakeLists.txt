add_subdirectory(rttr)

add_subdirectory(glfw)
target_compile_options(glfw PUBLIC /wd4819)

add_subdirectory(spdlog)
target_compile_options(spdlog PUBLIC /wd4819)

add_subdirectory(glad)
target_compile_options(glad PUBLIC /wd4819)

add_subdirectory(assimp)
target_compile_options(assimp PUBLIC /wd4819)

set(EASY_PROFILER_NO_GUI ON CACHE BOOL "")
set(EASY_PROFILER_NO_SAMPLES ON CACHE BOOL "")
add_subdirectory(easy_profiler)

add_subdirectory(glm)

#build imgui, because imgui does not have own CMakeLists.txt
set(IMGUI_DIR ../third_party/imgui)
add_library(imgui
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_demo.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)
target_compile_options(imgui PUBLIC /wd4819)
target_include_directories(imgui PRIVATE "${IMGUI_DIR}")

# include glfw for imgui
target_include_directories(imgui PRIVATE "../third_party/glfw/include")