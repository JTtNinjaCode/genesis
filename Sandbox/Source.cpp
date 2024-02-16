#include <Genesis.h>

#include <iostream>

class ExampleLayer : public Genesis::Layer {
 public:
  ExampleLayer() : Layer("exmaple") {}
  //void OnUpdate() { LOG_TRACE("{0} layer call OnUpdate", GetName()); }
  //void OnEvent() { LOG_TRACE("{0} layer call OnEvent", GetName()); }
};

class SandBox : public Genesis::Application {
 public:
  SandBox() { PushLayer(new ExampleLayer); }
  ~SandBox() {}
};

std::unique_ptr<Genesis::Application> Genesis::CreateApplication() {
  return std::make_unique<SandBox>();
}
