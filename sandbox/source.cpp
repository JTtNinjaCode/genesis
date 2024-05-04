#include <Genesis.h>
#include <core/entry_point.h>
#pragma warning(push)
#pragma warning(disable : 4005)
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma warning(pop)

#include "imgui_layer/sandbox_2d.h"
#include "imgui_layer/sandbox_3d.h"

using namespace genesis;
class Sandbox : public Application {
 public:
  Sandbox() {
    PushOverLayer(std::make_shared<Sandbox3D>());
    PushOverLayer(std::make_shared<GridController>());
  }
  ~Sandbox() {}
};

Application* genesis::CreateApplication() { return new Sandbox; }
