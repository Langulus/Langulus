cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(LANGULUS_BUILD_SHARED_LIBRARIES "Build shared (so/dll) libraries" ON)

# MSVC adds additional dependencies that interfere when libraries are       
# combined into a single shared library. This avoid it...                   
# https://stackoverflow.com/questions/41400536                              
message("Additional dependencies removed: ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_CXX_STANDARD_LIBRARIES "")

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

# Check if this project is built as standalone, or a part of something else 
if(PROJECT_IS_TOP_LEVEL)
    add_compile_definitions(LANGULUS_ENABLE_TESTING)
    enable_testing()
endif()

if(LANGULUS_BUILD_SHARED_LIBRARIES)
    set(LANGULUS_LIBRARY_TYPE SHARED)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    add_compile_definitions(LANGULUS_EXPORT_ALL)
else()
    set(LANGULUS_LIBRARY_TYPE STATIC)
    set(CMAKE_POSITION_INDEPENDENT_CODE OFF)
endif()

add_subdirectory(Core)
add_subdirectory(Logger)
add_subdirectory(RTTI)
add_subdirectory(SIMD)
add_subdirectory(Anyness)
add_subdirectory(Flow)
add_subdirectory(Entity)
add_subdirectory(Math)

# Combine all submodules as one library                                     
add_library(Langulus.Framework ${LANGULUS_LIBRARY_TYPE}
    $<TARGET_OBJECTS:Langulus.Logger>
    $<TARGET_OBJECTS:Langulus.RTTI>
    $<TARGET_OBJECTS:Langulus.Anyness>
    $<TARGET_OBJECTS:Langulus.Flow>
    $<TARGET_OBJECTS:Langulus.Entity>
)

target_include_directories(Langulus.Framework
    PUBLIC	    include
                Logger/include
                RTTI/include
                Anyness/include
                Flow/include
                Entity/include
)

target_link_libraries(Langulus.Framework
    INTERFACE   Langulus.Core
                Langulus.SIMD
                Langulus.Math
)

if(NOT MSVC)
    target_link_libraries(Langulus.Framework PRIVATE dl)
endif()

if(PROJECT_IS_TOP_LEVEL)
    remove_definitions(-DLANGULUS_EXPORT_ALL)
    add_subdirectory(testmodule)
    add_subdirectory(test)
endif()