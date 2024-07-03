add_subdirectory(rttr)

add_subdirectory(glfw)
target_compile_options(glfw PUBLIC /wd4819)

add_subdirectory(spdlog)
target_compile_options(spdlog PUBLIC /wd4819)

add_subdirectory(glad)
target_compile_options(glad PUBLIC /wd4819)

add_subdirectory(assimp)
target_compile_options(assimp PUBLIC /wd4819)

add_subdirectory(freetype2)
target_compile_definitions(freetype PRIVATE CMAKE_BUILD_TYPE=Release)
target_compile_options(freetype PUBLIC /wd4819)

add_subdirectory(sol2)
target_compile_options(assimp PUBLIC /wd4819)

set(EASY_PROFILER_NO_GUI ON CACHE BOOL "")
set(EASY_PROFILER_NO_SAMPLES ON CACHE BOOL "")
add_subdirectory(easy_profiler)

add_subdirectory(glm)

set(STB_INCLUDE_DIRS "stb")
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${STB_INCLUDE_DIRS})

#link library
set(FMOD_STUDIO_INCLUDE_DIRS "fmod/studio/inc")
set(FMOD_INCLUDE_DIRS "fmod/core/inc")
find_library(FMOD_STUDIO_LIB NAMES "fmodstudio_vc" HINTS "fmod/studio/lib/x64")
find_library(FMOD_LIB NAMES "fmod_vc" HINTS "fmod/core/lib/x64")
file(COPY "fmod/studio/lib/x64/fmodstudio.dll" DESTINATION "../sandbox")
file(COPY "fmod/core/lib/x64/fmod.dll" DESTINATION "../sandbox")
add_library(fmod STATIC IMPORTED GLOBAL)
add_library(fmod_studio STATIC IMPORTED GLOBAL)
set_target_properties(fmod PROPERTIES IMPORTED_LOCATION "${FMOD_LIB}")
set_target_properties(fmod_studio PROPERTIES IMPORTED_LOCATION "${FMOD_STUDIO_LIB}")
target_include_directories(fmod INTERFACE "${FMOD_INCLUDE_DIRS}")
target_include_directories(fmod_studio INTERFACE "${FMOD_STUDIO_INCLUDE_DIRS}")

set(IMGUI_DIR "imgui")
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
target_include_directories(imgui PRIVATE "./glfw/include")