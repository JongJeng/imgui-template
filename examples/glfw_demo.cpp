#include <imgui.h>
#include <implot.h>

#include "glfw_opengl3_app.hpp"

int main(int /*unused*/, char** /*unused*/) {
  // NOLINTNEXTLINE(readability-magic-numbers)
  imguiplot::GlfwOpenGL3App app({.window_width = 1920, .window_height = 1080, .font_path = "MSYH.TTC"});

  return app.Run([] {
    ImGui::ShowDemoWindow();
    ImPlot::ShowDemoWindow();
  });
}
