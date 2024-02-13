#include <Genesis.h>

#include <iostream>
class SandBox : public Genesis::Application {
 public:
  SandBox() {}
  ~SandBox() {}
};

std::unique_ptr<Genesis::Application> Genesis::CreateApplication() {
  return std::make_unique<SandBox>();
}
