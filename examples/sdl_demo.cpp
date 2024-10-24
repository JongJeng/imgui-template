#include <imgui.h>
#include <implot.h>

#include "sdl3_renderer3_app.hpp"

int main(int /*unused*/, char** /*unused*/) {
  // NOLINTNEXTLINE(readability-magic-numbers)
  imguiplot::SdlRendererApp app({.window_width = 1600, .window_height = 900});

  return app.Run([] {
    ImGui::ShowDemoWindow();
    ImPlot::ShowDemoWindow();
  });
}
