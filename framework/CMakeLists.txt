cmake_minimum_required(VERSION 3.22)

# MSVC adds additional dependencies that interfere when libraries are       
# combined into a single shared library. This avoid it...                   
# https://stackoverflow.com/questions/41400536                              
message("Additional dependencies removed: ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_CXX_STANDARD_LIBRARIES "")

project(Langulus.Framework)

if(LANGULUS_BUILD_SHARED_LIBRARIES)
    # These settings are for the subdirectories                             
    set(LANGULUS_LIBRARY_TYPE OBJECT)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    add_compile_definitions(LANGULUS_EXPORT_ALL)
else()
    # These settings are for the subdirectories                             
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

if(LANGULUS_BUILD_SHARED_LIBRARIES)
    # These settings are for the framework                                  
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    set(LANGULUS_LIBRARY_TYPE SHARED)
else()
    # These settings are for the framework                                  
    set(LANGULUS_LIBRARY_TYPE STATIC)
endif()

# Combine all submodules as one library                                     
message("Building Langulus as: ${LANGULUS_LIBRARY_TYPE} library")
add_library(Langulus.Framework ${LANGULUS_LIBRARY_TYPE} Empty.cpp)

target_include_directories(Langulus.Framework PUBLIC include)

target_link_libraries(Langulus.Framework
    PUBLIC  Langulus.Core
            Langulus.Logger
            Langulus.RTTI
            Langulus.SIMD
            Langulus.Anyness
            Langulus.Flow
            Langulus.Entity
            Langulus.Math
            fmt
)

if(NOT MSVC)
    target_link_libraries(Langulus.Framework PRIVATE dl)
endif()

if(BUILD_TESTING)
    add_subdirectory(testmodule)
    add_subdirectory(test)

    add_custom_command(
        TARGET Langulus.Framework POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:Langulus.Framework>" "$<TARGET_FILE_DIR:Test.Framework>"
        COMMENT "Copying `$<TARGET_FILE:Langulus.Framework>` to `$<TARGET_FILE_DIR:Test.Framework>`"
    )
endif()