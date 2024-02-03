#include <Genesis.h>

#include <iostream>
class SandBox : public Genesis::Application {
 public:
  SandBox() {}
  void Run() { std::cout << "Hi" << std::endl; }
  ~SandBox() {}
};
int main() {
  SandBox s;
  s.Run();
}