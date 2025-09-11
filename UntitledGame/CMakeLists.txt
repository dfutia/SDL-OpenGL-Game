# CMakeLists.txt : CMake project for UntitledGame.
# Includes source files and defines project-specific logic.

find_package(OpenGL REQUIRED)

# Add source files to this project's executable.
add_executable(UntitledGame
    "${CMAKE_SOURCE_DIR}/vendor/glad/src/glad.c"

    "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui.cpp"
    "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp"
    "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp"
    "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp"
    "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp"

    "${CMAKE_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_sdl2.cpp"
    "${CMAKE_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp"

    "main.cpp"
    "core/input.h"
    "core/window.h"
    "platform/sdl/sdlwindow.h"      "platform/sdl/sdlwindow.cpp"
    "platform/sdl/sdlinput.h"       "platform/sdl/sdlinput.cpp"
    "core/game.h"                   "core/game.cpp"
    
    "renderer/renderer.h"
    "platform/gl/glrenderer.h"      "platform/gl/glrenderer.cpp"
    "renderer/camera.h"
    "renderer/mesh.h"
    "core/world.h"
    "renderer/resourcemanager.cpp"
    "core/services.h"               "core/services.cpp"
    "platform/gl/glshader.cpp"
    "platform/gl/glbuffer.cpp"
 "core/platform.h" "platform/sdl/sdlplatform.h" "platform/sdl/sdlplatform.cpp")

# Copy assets directory to build output after build.
add_custom_command(
    TARGET UntitledGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:UntitledGame>/assets
)

# Include directories for the target.
target_include_directories(UntitledGame PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/vendor/SDL2/include"
    "${CMAKE_SOURCE_DIR}/vendor/glad/include"
    "${CMAKE_SOURCE_DIR}/vendor/glm"
    "${CMAKE_SOURCE_DIR}/vendor/imgui"         
    "${CMAKE_SOURCE_DIR}/vendor/imgui/backends" 
)

# Link against libraries.
target_link_libraries(UntitledGame PRIVATE
    OpenGL::GL
    "${CMAKE_SOURCE_DIR}/vendor/SDL2/lib/x64/SDL2.lib"
    "${CMAKE_SOURCE_DIR}/vendor/SDL2/lib/x64/SDL2main.lib"
)

# Set C++ standard if supported.
if(CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET UntitledGame PROPERTY CXX_STANDARD 23)
endif()

# TODO: Add tests and install targets if needed.
