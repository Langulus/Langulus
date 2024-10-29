cmake_minimum_required(VERSION 3.28)
project(LangulusRoot
    VERSION         1.0.0
    DESCRIPTION     "The Langulus SDK, containing the entire framework, tools, and modules"
    HOMEPAGE_URL    https://langulus.com
)

include(LangulusUtilities.cmake)

option(LANGULUS_TOASTER_MODE "Removes all modules that require massive dependencies, graphical acceleration, desktop environments, etc." ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Add Langulus::Core first, because we need the cached variables		
langulus_init_git_submodule(framework/Core)
add_subdirectory(framework/Core)

if(LANGULUS_TESTING)
    enable_testing()
endif()

# Add framework                                                         
add_subdirectory(framework)

# Add plugins                                                           
add_subdirectory(mods)
