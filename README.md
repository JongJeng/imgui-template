
# imgui-template

Multiplatform (ImGui + ImPlot + CMake) application template.

Quickly prototype applications with the ImGui / ImPlot libraries:

```cpp
#include <imgui.h>
#include <implot.h>
#include <sdl_renderer_app.hpp>

int main(int, char**) {
  imguiplot::SdlRendererApp app({
    .window_width = 1600, 
    .window_height = 900
  });

  return app.Run([] {
    ImGui::ShowDemoWindow();
    ImPlot::ShowDemoWindow();
  });
}
```

## Prerequisites

A compiler with C++17 support and at least one of the supported backend libraries: [SDL](https://github.com/libsdl-org/SDL), [GLFW](https://github.com/glfw/glfw).

## Build


### Library

Use this repository as a submodule / subfolder and link to the `imguiplot-backend-app` target in your CMake file.


Your CMake file:

```cmake
cmake_minimum_required(VERSION 3.21)

project(my-imguiplot-demo)
set(CMAKE_CXX_STANDARD 17)
add_subdirectory(imguiplot-app)

add_executable(my-demo demo.cpp)
target_link_libraries(my-demo imguiplot-glfw-app imgui)

# copy a font file next to the executable
copy_file(my-demo "${IMGUI_FONT_DIR}/ProggyClean.ttf")
```

Your cpp file:

```cpp
#include <imgui.h>
#include <glfw_opengl3_app.hpp>

int main(int, char**) {
  imguiplot::GlfwOpenGL3App app({
    .font_path = "ProggyClean.ttf",
    .font_size = 24
  });

  return app.Run([] {
    ImGui::Begin("Demo");
    ImGui::Text("Hello, world!");
    ImGui::End(); 
  });
}
```
