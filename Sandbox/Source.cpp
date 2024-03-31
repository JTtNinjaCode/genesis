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
#include "platform/render_api/opengl/opengl_shader.h"

class Sandbox : public genesis::Application {
 public:
  Sandbox() { PushOverLayer(std::make_shared<Sandbox2D>()); }
  ~Sandbox() {}
};

genesis::Application* genesis::CreateApplication() {
  genesis::Log::Init();
  CORE_LOG_WARN("Initialized Log!");

  return new Sandbox;
}
