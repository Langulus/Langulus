#																			
#	This is a template external module for testing runtime loading of		
#	Langulus modules by Test.Framework										
#																			
project(Langulus.Test.Module)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCE_FILES)

# We're importing symbols from Langulus.Framework                           
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)
remove_definitions(-DLANGULUS_EXPORT_ALL)
if(NOT WIN32)
    add_compile_options(-fvisibility=hidden)
endif()

add_library(Mod.Test SHARED ${SOURCE_FILES})
target_link_libraries(Mod.Test PRIVATE Langulus.Framework)

add_custom_command(
    TARGET Mod.Test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:Mod.Test>" "$<TARGET_FILE_DIR:Test.Framework>"
    COMMENT "Copying `$<TARGET_FILE:Mod.Test>` to `$<TARGET_FILE_DIR:Test.Framework>`"
)
