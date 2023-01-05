#																			
#	This is a template external module for testing runtime loading of		
#	Langulus modules by Test.Framework										
#																			
project(Langulus.Test.Module)
langulus_import_framework()

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} LANGULUS_TESTMODULE_SOURCES)
add_library(Mod.Test SHARED ${LANGULUS_TESTMODULE_SOURCES})

target_link_libraries(Mod.Test PRIVATE Langulus.Framework)
