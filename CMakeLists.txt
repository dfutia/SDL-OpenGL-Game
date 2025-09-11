# CMakeLists.txt : Top-level CMake project file.
# Handles global configuration and includes sub-projects.

cmake_minimum_required(VERSION 3.20)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(
        CMAKE_MSVC_DEBUG_INFORMATION_FORMAT
        "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>"
    )
endif()

project(UntitledGame)

# Include sub-projects.
add_subdirectory("UntitledGame")
