# CMakeList.txt : CMake project for UntitledGame, include source and define
# project specific logic here.
#

find_package(OpenGL REQUIRED)

# Add source to this project's executable.
add_executable (UntitledGame 
    "${CMAKE_SOURCE_DIR}/vendor/glad/src/glad.c" 
    "main.cpp" 
    "core/input.h"
    "core/window.h"
    "platform/sdl/sdlwindow.h" "platform/sdl/sdlwindow.cpp"
    "platform/sdl/sdlinput.h" "platform/sdl/sdlinput.cpp"
 "core/game.h" "core/game.cpp" "platform/sdl/sdlcontext.h" "renderer/renderer.h" "platform/gl/glrenderer.h" "platform/gl/glrenderer.cpp" "renderer/camera.h" "renderer/mesh.h" "core/world.h")

target_include_directories(UntitledGame PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"   
    "${CMAKE_SOURCE_DIR}/vendor/SDL2/include"
    "${CMAKE_SOURCE_DIR}/vendor/glad/include"
    "${CMAKE_SOURCE_DIR}/vendor/glm"
)

target_link_libraries(UntitledGame PRIVATE 
    OpenGL::GL
    "${CMAKE_SOURCE_DIR}/vendor/SDL2/lib/x64/SDL2.lib"
    "${CMAKE_SOURCE_DIR}/vendor/SDL2/lib/x64/SDL2main.lib"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET UntitledGame PROPERTY CXX_STANDARD 23)
endif()

# TODO: Add tests and install targets if needed.
