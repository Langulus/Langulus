cmake_minimum_required(VERSION 3.28)
project(LangulusRoot
    VERSION         1.0.0
    DESCRIPTION     "The Langulus SDK, containing the entire framework, tools, and modules"
    HOMEPAGE_URL    https://langulus.com
)

# Disable the FetchContent requests for langulus libraries from here on			
set(LANGULUS ON CACHE INTERNAL 
"Defines the build tree as a part of Langulus,  \
thus prevents the downloading of base Langulus libraries. \
They should be in the build tree already!" FORCE)

option(LANGULUS_TOASTER_MODE "Removes all modules that require massive dependencies, \
like graphics acceleration, desktop environments, etc. This is enabled by default to avoid \
downloading a lot of stuff on the initial configuration without the user's consent. \
Even if this is enabled, you will still be required to manually download large SDKs like Vulkan for now." ON)

set(LANGULUS_EXTERNAL_DIRECTORY "${CMAKE_SOURCE_DIR}/external" CACHE PATH
"Place where external dependencies will be downloaded")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
include(LangulusUtilities.cmake)

if (LANGULUS_TESTING)
	enable_testing()
endif()

# Add framework																	
add_subdirectory(framework)

# Add plugins																	
add_subdirectory(mods)
