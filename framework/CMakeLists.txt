project(Langulus)

langulus_init_git_submodule(Core)
add_subdirectory(Core)
langulus_init_git_submodule(Logger)
add_subdirectory(Logger)
langulus_init_git_submodule(RTTI)
add_subdirectory(RTTI)
langulus_init_git_submodule(SIMD)
add_subdirectory(SIMD)
langulus_init_git_submodule(Anyness)
add_subdirectory(Anyness)
langulus_init_git_submodule(Flow)
add_subdirectory(Flow)
langulus_init_git_submodule(Entity)
add_subdirectory(Entity)
langulus_init_git_submodule(Math)
add_subdirectory(Math)

# Combine all submodules as one library                                     
message("Building Langulus as: ${LANGULUS_LIBRARY_TYPE} library")
add_library(Langulus ${LANGULUS_LIBRARY_TYPE} 
    $<TARGET_OBJECTS:LangulusLogger>
    $<TARGET_OBJECTS:LangulusRTTI>
    $<TARGET_OBJECTS:LangulusAnyness>
    $<TARGET_OBJECTS:LangulusFlow>
    $<TARGET_OBJECTS:LangulusEntity>
)

target_include_directories(Langulus
    PUBLIC      include
                $<TARGET_PROPERTY:LangulusLogger,INTERFACE_INCLUDE_DIRECTORIES>
                $<TARGET_PROPERTY:LangulusRTTI,INTERFACE_INCLUDE_DIRECTORIES>
                $<TARGET_PROPERTY:LangulusAnyness,INTERFACE_INCLUDE_DIRECTORIES>
                $<TARGET_PROPERTY:LangulusFlow,INTERFACE_INCLUDE_DIRECTORIES>
                $<TARGET_PROPERTY:LangulusMath,INTERFACE_INCLUDE_DIRECTORIES>
                $<TARGET_PROPERTY:LangulusEntity,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(Langulus
    PUBLIC      LangulusCore
                fmt
)

if(NOT MSVC)
    target_link_libraries(Langulus PRIVATE dl)
endif()

target_compile_definitions(Langulus
    PRIVATE     LANGULUS_EXPORT_ALL
)

if(LANGULUS_ENABLE_TESTING)
    add_subdirectory(test)
    add_subdirectory(testmodule)
    langulus_copy_dlls(LangulusTest ON Langulus)
endif()

