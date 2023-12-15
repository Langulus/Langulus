file(GLOB_RECURSE
	LANGULUS_TEST_SOURCES 
	LIST_DIRECTORIES FALSE CONFIGURE_DEPENDS
	*.cpp
)

add_executable(LangulusTest ${LANGULUS_TEST_SOURCES})

target_link_libraries(LangulusTest
    PRIVATE     Langulus
                Catch2
)

add_dependencies(LangulusTest
	LangulusModTest
)

add_test(
	NAME		LangulusTest
	COMMAND		LangulusTest
	WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)