cmake_minimum_required(VERSION 3.22)

# MSVC adds additional dependencies that interfere when libraries are       
# combined into a single shared library. This avoid it...                   
# https://stackoverflow.com/questions/41400536                              
message("Additional dependencies: ${CMAKE_CXX_STANDARD_LIBRARIES}")
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

add_subdirectory(Core)
add_subdirectory(Logger)
add_subdirectory(RTTI)
add_subdirectory(SIMD)
add_subdirectory(Anyness)
add_subdirectory(Flow)
add_subdirectory(Entity)
add_subdirectory(Math)

# Combine all submodules as one shared library                              
add_library(Langulus.Framework SHARED Empty.cpp)
target_link_libraries(Langulus.Framework
    INTERFACE   Langulus.Core
                Langulus.SIMD
                Langulus.Math
    PUBLIC      Langulus.Logger
                Langulus.RTTI
                Langulus.Anyness
                Langulus.Flow
                Langulus.Entity
)

# By default, symbols provided by the submodules that are not used by       
# Langulus.Framework (which is all of them in this case) are discarded.     
# This makes sure that everything is exported.                              
if(WIN32)
    set_target_properties(Langulus.Framework
        PROPERTIES LINK_FLAGS "/WHOLEARCHIVE"
    )
elseif(APPLE)
    set_target_properties(Langulus.Framework
        PROPERTIES LINK_FLAGS "-Wl,-all_load"
    )
else()
    set_target_properties(Langulus.Framework
        PROPERTIES LINK_FLAGS "-Wl,--whole-archive"
    )
endif()