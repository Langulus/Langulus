cmake_minimum_required(VERSION 3.30)
project(Langulus
   VERSION         1.0.0
   DESCRIPTION     "The Langulus SDK, containing the entire framework, tools, and modules"
   HOMEPAGE_URL    https://langulus.com
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(LANGULUS_OPTION_TESTING OFF)

if (MSVC)
   set(CMAKE_CXX_FLAGS             "${CMAKE_CXX_FLAGS}             ${LANGULUS_COVERAGE_COMPILER_FLAGS_MSVC}    ${LANGULUS_SANITIZE_COMPILER_FLAGS_MSVC}")
   set(CMAKE_C_FLAGS               "${CMAKE_C_FLAGS}               ${LANGULUS_COVERAGE_COMPILER_FLAGS_MSVC}    ${LANGULUS_SANITIZE_COMPILER_FLAGS_MSVC}")
   set(CMAKE_EXE_LINKER_FLAGS      "${CMAKE_EXE_LINKER_FLAGS}      ${LANGULUS_COVERAGE_LINKER_FLAGS_MSVC}      ${LANGULUS_SANITIZE_LINKER_FLAGS_MSVC}")
   set(CMAKE_SHARED_LINKER_FLAGS   "${CMAKE_SHARED_LINKER_FLAGS}   ${LANGULUS_SANITIZE_LINKER_FLAGS_MSVC}")
   #set(CMAKE_MODULE_LINKER_FLAGS  "${CMAKE_MODULE_LINKER_FLAGS}   ${LANGULUS_SANITIZE_LINKER_FLAGS_MSVC}")
   set(CMAKE_STATIC_LINKER_FLAGS   "${CMAKE_STATIC_LINKER_FLAGS}   ${LANGULUS_SANITIZE_LINKER_FLAGS_MSVC}")
else()
   set(CMAKE_CXX_FLAGS             "${CMAKE_CXX_FLAGS}             ${LANGULUS_COVERAGE_COMPILER_FLAGS}         ${LANGULUS_SANITIZE_COMPILER_FLAGS}")
   set(CMAKE_C_FLAGS               "${CMAKE_C_FLAGS}               ${LANGULUS_COVERAGE_COMPILER_FLAGS}         ${LANGULUS_SANITIZE_COMPILER_FLAGS}")
   set(CMAKE_EXE_LINKER_FLAGS      "${CMAKE_EXE_LINKER_FLAGS}      ${LANGULUS_COVERAGE_LINKER_FLAGS}           ${LANGULUS_SANITIZE_LINKER_FLAGS}")
   set(CMAKE_SHARED_LINKER_FLAGS   "${CMAKE_SHARED_LINKER_FLAGS}   ${LANGULUS_SANITIZE_LINKER_FLAGS}")
   #set(CMAKE_MODULE_LINKER_FLAGS  "${CMAKE_MODULE_LINKER_FLAGS}   ${LANGULUS_SANITIZE_LINKER_FLAGS}")
   set(CMAKE_STATIC_LINKER_FLAGS   "${CMAKE_STATIC_LINKER_FLAGS}   ${LANGULUS_SANITIZE_LINKER_FLAGS}")
endif()

cmake_path (GET PROJECT_BINARY_DIR STEM LAST_ONLY LANGULUS_BUILD_IDENTIFIER)
message (STATUS "[LANGULUS] Build identifier: \"${LANGULUS_BUILD_IDENTIFIER}\"")

# Disable the FetchContent requests for langulus libraries from here on			
set(LANGULUS ON CACHE INTERNAL 
"Defines the build tree as a part of Langulus,  \
thus preventing the downloading of base Langulus libraries. \
They should be in the build tree already!" FORCE)

option(LANGULUS_TOASTER_MODE
"Removes all modules that require massive dependencies, \
like graphics acceleration, desktop environments, etc. This is enabled by default to avoid \
downloading a lot of stuff on the initial configuration without the user's consent. \
Even if this is disabled, you will still be required to manually download large SDKs like Vulkan." ON)

set(LANGULUS_PERCIST_DIRECTORY "${CMAKE_SOURCE_DIR}/percist/${LANGULUS_BUILD_IDENTIFIER}" CACHE PATH
"Place where reports from different builds end up, \
so we can keep track of build time and performance")

set(LANGULUS_EXTERNAL_DIRECTORY "${CMAKE_SOURCE_DIR}/external" CACHE PATH
"Place where external dependencies will be downloaded")

# It is very important these are set before any targets are introduced		
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Include tests                                                               
if (LANGULUS_OPTION_TESTING)
   enable_testing()
endif()

# Initialize and update a submodule
function(langulus_init_git_submodule NAME)
   if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${NAME}/CMakeLists.txt" )
      # Submodule hasn't been initialized yet, so call git submodule update --init on it
      message(STATUS "[LANGULUS] Initializing submodule: ${CMAKE_CURRENT_SOURCE_DIR}/${NAME}...")
      find_package(Git REQUIRED)
      execute_process(
         COMMAND                 ${GIT_EXECUTABLE} submodule update --init -- ${NAME} 
         WORKING_DIRECTORY       ${CMAKE_CURRENT_SOURCE_DIR}
         COMMAND_ERROR_IS_FATAL  ANY
      )
   endif()
   add_subdirectory(${NAME})
endfunction()

# Add framework																	
add_subdirectory(framework)

# Add plugins																	
add_subdirectory(mods)

if(LANGULUS_OPTION_TESTING)
   add_subdirectory(tests)
endif()