#																			
#	This is a template external module for testing runtime loading of		
#	Langulus modules 										                
#																			
add_library(LangulusModTest SHARED Main.cpp)
target_link_libraries(LangulusModTest PRIVATE Langulus)

langulus_copy_dlls_advanced(LangulusModTest
	TO		LangulusTest
	FROM	LangulusModTest
)