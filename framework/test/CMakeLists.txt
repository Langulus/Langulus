project(Langulus.Test.Framework)
langulus_import_framework()

# Configure Catch2 library                                                  
download_project(
    PROJ                Catch2
    GIT_REPOSITORY      https://github.com/catchorg/Catch2.git
    GIT_TAG             v2.x
    UPDATE_DISCONNECTED 1
)
add_subdirectory(${Catch2_SOURCE_DIR} ${Catch2_BINARY_DIR})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} LANGULUS_FRAMEWORK_TEST_SOURCES)
add_executable(Test.Framework ${LANGULUS_FRAMEWORK_TEST_SOURCES})

target_link_libraries(Test.Framework
    PRIVATE     Langulus.Framework
                Catch2
)

add_dependencies(Test.Framework Mod.Test)
langulus_copy_dlls(
	TO		Test.Framework
	FROM	Langulus.Framework Mod.Test
)

add_test(NAME Test.Framework COMMAND Test.Framework)
