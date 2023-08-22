cmake_minimum_required(VERSION 3.24)
project(LangulusRoot
    VERSION         1.0.0
    DESCRIPTION     "The Langulus SDK, containing the entire framework, tools, and modules"
    HOMEPAGE_URL    https://langulus.com
)

message("Compiler: ${CMAKE_CXX_COMPILER_ID} - ${CMAKE_CXX_COMPILER_VERSION}")
set(LANGULUS ON CACHE INTERNAL "Defines the build tree as Langulus")

# Populate the cmake directory											
include(LangulusUtilities.cmake)
langulus_fetch_cmake()

# Handle feature flags and global definitions/requirements				
include(HandleLangulusFeatures)
handle_langulus_features()

# Add framework															
add_subdirectory(framework)

# Add plugins															
add_subdirectory(mods)
