add_executable(LangulusTest
    Main.cpp
    TestModule.cpp
)

target_link_libraries(LangulusTest
    PRIVATE     Langulus
                Catch2
)

add_test(
	NAME		LangulusTest
	COMMAND		LangulusTest
	WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)