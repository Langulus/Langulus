cmake_minimum_required(VERSION 3.24)
project(LangulusRoot
    VERSION         1.0.0
    DESCRIPTION     "The Langulus SDK, containing the entire framework, tools, and modules"
    HOMEPAGE_URL    https://langulus.com
)

option(LANGULUS_TOASTER_MODE "Removes all modules that require massive dependencies, like Vulkan" ON)
set(LANGULUS_TESTING OFF CACHE BOOL "Disable testing by default")

# Add framework                                                         
include(LangulusUtilities.cmake)
add_subdirectory(framework)

# Add plugins                                                           
add_subdirectory(mods)
