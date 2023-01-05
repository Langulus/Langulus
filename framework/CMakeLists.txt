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

langulus_init_git_submodule(Core)
add_subdirectory(Core)
langulus_init_git_submodule(Logger)
add_subdirectory(Logger)
langulus_init_git_submodule(RTTI)
add_subdirectory(RTTI)
langulus_init_git_submodule(SIMD)
add_subdirectory(SIMD)
langulus_init_git_submodule(Anyness)
add_subdirectory(Anyness)
langulus_init_git_submodule(Flow)
add_subdirectory(Flow)
langulus_init_git_submodule(Entity)
add_subdirectory(Entity)
langulus_init_git_submodule(Math)
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
endif()