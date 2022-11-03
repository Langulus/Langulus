project(Langulus.Test.Framework)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCE_FILES)

# We're importing symbols from Langulus.Framework                           
remove_definitions(-DLANGULUS_EXPORT_ALL)
if(NOT WIN32)
    add_compile_options(-fvisibility=hidden)
endif()

# Configure Catch2 library                                                  
message(STATUS "Configuring external project: Catch2...")
download_project(
    PROJ                Catch2
    GIT_REPOSITORY      https://github.com/catchorg/Catch2.git
    GIT_TAG             v2.x
    UPDATE_DISCONNECTED 1
)

add_subdirectory(${Catch2_SOURCE_DIR} ${Catch2_BINARY_DIR})
add_executable(Test.Framework ${SOURCE_FILES})

target_link_libraries(Test.Framework PRIVATE Langulus.Framework Catch2)
add_dependencies(Test.Framework Test.Module)

add_test(NAME Test.Framework COMMAND Test.Framework)
