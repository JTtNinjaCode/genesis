#include "playground.h"

#include <chrono>

#include "genesis.h"
Playground::Playground() : ImGuiLayer("playground") {
  ShaderLibrary::AddShader("test", "assets/shaders/test.vert", "assets/shaders/test.frag");
}

void Playground::OnUpdate(TimeStep time_step) {}

void Playground::OnRender() {
  RenderCommand::GetInstance().Clear();
  auto& renderer_3d = Renderer3D();

  static float quadVertices[] = {-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f};
  static std::shared_ptr<VertexBuffer> vb = VertexBuffer::Create(quadVertices, sizeof(quadVertices));
  static const BufferLayout bl({MathDataType::kFloat2});
  static std::shared_ptr<VertexArray> va = VertexArray::Create(bl);
  static std::shared_ptr<Texture2D> t = Texture2D::Create("assets\\textures\\cherno.png", TextureType::kDiffuse);
  va->SetVertexBuffer(vb);
  t->Bind(0);
  auto& test = ShaderLibrary::GetShader("test");
  static auto begin_time = std::chrono::high_resolution_clock().now();
  auto ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock().now() - begin_time);
  test.Bind();
  test.SetUniform("u_origin_texture", 0);
  test.SetUniform("u_resolution", glm::vec2(1000, 1000));
  test.SetUniform("u_time", ms.count() / 1000.0f);
  renderer_3d.Submit(test, *va, glm::mat4{1.0f}, nullptr);
}

void Playground::OnImguiRender() {}

EventState Playground::OnEvent(Event& event) { return EventState(); }