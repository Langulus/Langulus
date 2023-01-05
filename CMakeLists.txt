cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(LANGULUS_BUILD_SHARED_LIBRARIES "Build shared (so/dll) libraries" ON)

project(Langulus)

include(InitializeGitSubmodule.cmake)
langulus_init_git_submodule(cmake)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(FetchLangulusModule)
include(HandleLangulusFeatures)

handle_langulus_features()

add_compile_definitions(LANGULUS_ENABLE_TESTING)
enable_testing()
set(BUILD_TESTING ON CACHE BOOL "Enable testing")

add_subdirectory(framework)

langulus_init_git_submodule(mods/Mod-GLFW)
add_subdirectory(mods/Mod-GLFW)
langulus_init_git_submodule(mods/Mod-ImGui)
add_subdirectory(mods/Mod-ImGui)
