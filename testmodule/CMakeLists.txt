#																			
#	This is a template external module for testing runtime loading of		
#	Langulus modules by Test.Framework										
#																			
project(Langulus.Test.Module)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCE_FILES)

if(NOT WIN32)
    add_compile_options(-fvisibility=hidden)
endif()

add_library(Test.Module SHARED ${SOURCE_FILES})
target_link_libraries(Test.Module PRIVATE Langulus.Framework)
