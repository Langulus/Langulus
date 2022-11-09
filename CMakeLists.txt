cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(LANGULUS_BUILD_SHARED_LIBRARIES "Build shared (so/dll) libraries" ON)

project(Langulus)

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

add_compile_definitions(LANGULUS_ENABLE_TESTING)
enable_testing()
set(BUILD_TESTING ON)

add_subdirectory(framework)
