# SDL library
# sdl3 + sdlrenderer3(OpenGL/Direct3D/Metal/Vulkan)
 
find_package(SDL3 QUIET)

if (SDL3_FOUND)
  add_library(imguiplot-sdl-app STATIC
    sdl3_renderer3_app.cpp
    ../external/imgui/backends/imgui_impl_sdl3.cpp
    ../external/imgui/backends/imgui_impl_sdlrenderer3.cpp
  )

  target_include_directories(imguiplot-sdl-app PUBLIC
    .
    ${SDL3_INCLUDE_DIRS}
    ../external/imgui/backends
  )
  target_link_libraries(imguiplot-sdl-app PUBLIC
    ${SDL3_LIBRARIES}
    imgui
    implot
  )
endif()

message(STATUS "SDL3_FOUND: ${SDL3_FOUND}")

#################################################################

# GLFW library
# glfw + opengl3

find_package(glfw3 QUIET)
find_package(OpenGL QUIET)

if (glfw3_FOUND AND OpenGL_FOUND)
  add_library(imguiplot-glfw-app STATIC
    glfw_opengl3_app.cpp
    ../external/imgui/backends/imgui_impl_glfw.cpp
    ../external/imgui/backends/imgui_impl_opengl3.cpp
  )

  target_include_directories(imguiplot-glfw-app PUBLIC
    .
    ../external/imgui/backends
  )

  target_link_libraries(imguiplot-glfw-app PUBLIC
    glfw OpenGL::GL
    imgui implot dl
  )
endif()

message(STATUS "glfw3_FOUND: ${glfw3_FOUND}")
message(STATUS "OpenGL_FOUND: ${OpenGL_FOUND}")
