#include <Genesis.h>

#include <iostream>
#include <memory>
class SandBox : public Genesis::Application {
 public:
  SandBox() {}
  ~SandBox() {}
};

Genesis::Application* Genesis::CreateApplication() {
  return new SandBox();
}
