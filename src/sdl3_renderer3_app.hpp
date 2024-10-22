#pragma once

#include <cstdio>

#include <SDL3/SDL.h>

#include "app_base.hpp"
#include "options.hpp"

#if !SDL_VERSION_ATLEAST(3,0,0)
#error This backend requires SDL 3.0.0+
#endif

namespace imguiplot {

class Sdl3Renderer3Backend {
 public:
  using OptionsType = options::Generic;

  explicit Sdl3Renderer3Backend(OptionsType options)
      : options_(std::move(options)) {}
  ~Sdl3Renderer3Backend();

  // Disable copy due to owned resources:
  // SDL context, window, renderer, ImGui context, ImPlot context
  Sdl3Renderer3Backend(const Sdl3Renderer3Backend&) = delete;
  Sdl3Renderer3Backend& operator=(const Sdl3Renderer3Backend&) = delete;

  // Move could be implemented, but it's not needed for now.
  Sdl3Renderer3Backend(Sdl3Renderer3Backend&&) = delete;
  Sdl3Renderer3Backend& operator=(Sdl3Renderer3Backend&&) = delete;

  bool Init();
  bool IsRunning();
  void NewFrame();
  void RenderFrame();

 private:
  bool init_success_ = false;

  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;

  OptionsType options_;
};

using SdlRendererApp = App<Sdl3Renderer3Backend>;

}  // namespace imguiplot
