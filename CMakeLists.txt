cmake_minimum_required(VERSION 3.22)
project(Langulus.Framework)

find_package(Git REQUIRED)
execute_process(
    COMMAND ${GIT_EXECUTABLE} submodule update --init -- cmake 
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND_ERROR_IS_FATAL ANY
)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(FetchLangulusModule)
include(HandleLangulusFeatures)
handle_langulus_features()

add_subdirectory(Core)
add_subdirectory(Logger)
add_subdirectory(RTTI)
add_subdirectory(SIMD)
add_subdirectory(Anyness)
add_subdirectory(Flow)
add_subdirectory(Entity)
add_subdirectory(Math)

# Combine all subdirectories as one shared library
add_library(Langulus.Framework SHARED)
target_link_libraries(Langulus.Framework
    PUBLIC Core
           Logger
           RTTI
           SIMD
           Anyness
           Flow
           Entity
           Math
)
