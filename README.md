# MatVGL (Matium Visual Gaming Library)
Cross platform game engine.

Example program:
----------------------------------------------------------
```c++
    // main.cpp
    #include <iostream>

    #include <MatVGL/MatVGL_Engine.hpp>

    using namespace MatVGL;

    int main(int argc, char *argv[]) {
      try {
        Engine::setWindowTitle("MatVGL-tests");
        Engine::start();
      } catch (Engine::StartFailure &e) {
        std::cout << e.what() << std::endl;
        return -1;
      }

      while (!Engine::getUserHasXedOut()) {
        Engine::startFrame();
        Engine::endFrame();
      }

      Engine::stop();

      return 0;
    }
```
---------------------------------------------------------
