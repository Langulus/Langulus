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
)

langulus_copy_dlls(LangulusTest ON LangulusTest)
