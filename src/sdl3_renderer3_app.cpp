// adapted from imgui/examples/example_sdl3_sdlrenderer3/main.cpp

#include "sdl3_renderer3_app.hpp"

#include <iostream>

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <implot.h>

namespace imguiplot {

bool Sdl3Renderer3Backend::Init() {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
    std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    return false;
  }

  uint32_t window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;
  window_ =
      SDL_CreateWindow(options_.window_title.c_str(), options_.window_width,
                       options_.window_height, window_flags);

  if (window_ == nullptr) {
    SDL_Log("Error creating SDL_Window!");
    return false;
  }

//   SDL_HideWindow(window_);

  renderer_ = SDL_CreateRenderer(window_, nullptr);
  SDL_SetRenderVSync(renderer_, 1);

  if (renderer_ == nullptr) {
    SDL_Log("Error creating SDL_Renderer!");
    return false;
  }
  SDL_SetWindowPosition(window_, SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED);
  SDL_ShowWindow(window_);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImPlot::CreateContext();

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsLight();

  ImGui_ImplSDL3_InitForSDLRenderer(window_, renderer_);
  ImGui_ImplSDLRenderer3_Init(renderer_);

  ImGuiIO& imgui_io = ImGui::GetIO();
  if (imgui_io.Fonts->AddFontFromFileTTF(
          options_.font_path.c_str(),
          options_.font_size * options_.gui_scale) == nullptr) {
    SDL_Log("Error loading font %s!", options_.font_path.c_str());
    return false;
  }

  ImGui::GetStyle().ScaleAllSizes(options_.gui_scale);

  init_success_ = true;
  return true;
}

Sdl3Renderer3Backend::~Sdl3Renderer3Backend() {
  if (init_success_) {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();

    ImPlot::DestroyContext();
    ImGui::DestroyContext();
  }

  if (renderer_ != nullptr) {
    SDL_DestroyRenderer(renderer_);
  }
  if (window_ != nullptr) {
    SDL_DestroyWindow(window_);
  }
  SDL_Quit();
}

bool Sdl3Renderer3Backend::IsRunning() {
  bool running = true;
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    ImGui_ImplSDL3_ProcessEvent(&event);
    if (event.type == SDL_EVENT_QUIT) {
      running = false;
    }
    if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
        event.window.windowID == SDL_GetWindowID(window_)) {
      running = false;
    }
  }
  return running;
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
void Sdl3Renderer3Backend::NewFrame() {
  ImGui_ImplSDLRenderer3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();
}

void Sdl3Renderer3Backend::RenderFrame() {
  ImGui::Render();
  SDL_SetRenderDrawColor(renderer_, options_.bg_color[0], options_.bg_color[1],
                         options_.bg_color[2], options_.bg_color[3]);
  SDL_RenderClear(renderer_);
  ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer_);
  SDL_RenderPresent(renderer_);
}

}  // namespace imguiplot
