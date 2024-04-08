#build imgui, because imgui does not have own CMakeLists.txt
set(IMGUI_DIR ../third_party/imgui)
add_library(imgui "${IMGUI_DIR}/imgui.cpp"
                  "${IMGUI_DIR}/imgui_demo.cpp"
                  "${IMGUI_DIR}/imgui_draw.cpp"
                  "${IMGUI_DIR}/imgui_tables.cpp"
                  "${IMGUI_DIR}/imgui_widgets.cpp"

                  "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
                  "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp")
target_include_directories(imgui PRIVATE "${IMGUI_DIR}")

# include glfw for imgui
target_include_directories(imgui PRIVATE "../third_party/glfw/include")
