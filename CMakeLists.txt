cmake_minimum_required(VERSION 3.24)
project(LangulusRoot
    VERSION         1.0.0
    DESCRIPTION     "The Langulus SDK, containing the entire framework, tools, and modules"
    HOMEPAGE_URL    https://langulus.com
)

set(LANGULUS ON CACHE INTERNAL "Defines the build tree as Langulus")

# Add framework															
include(LangulusUtilities.cmake)
add_subdirectory(framework)

# Add plugins															
add_subdirectory(mods)
