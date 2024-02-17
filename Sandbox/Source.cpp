#include <Genesis.h>

#include <iostream>
#include <memory>


class SandBox : public Genesis::Application {
 public:
  SandBox() { PushOverLayer(new Genesis::ImGuiLayer); }
  ~SandBox() {}
};

Genesis::Application* Genesis::CreateApplication() { return new SandBox; }
