project(Langulus
    VERSION         1.0.0
    DESCRIPTION     "Langulus library, used to develop mods and tools"
    HOMEPAGE_URL    https://langulus.com
)

langulus_init_git_submodule(Logger)
add_subdirectory(Logger)
langulus_init_git_submodule(RTTI)
add_subdirectory(RTTI)
if(LANGULUS_FEATURE_MANAGED_MEMORY)
    langulus_init_git_submodule(Fractalloc)
    add_subdirectory(Fractalloc)
endif()
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
    $<$<BOOL:${LANGULUS_FEATURE_MANAGED_MEMORY}>:$<TARGET_OBJECTS:LangulusFractalloc>>
    $<TARGET_OBJECTS:LangulusAnyness>
    $<TARGET_OBJECTS:LangulusFlow>
    $<TARGET_OBJECTS:LangulusMath>
    $<TARGET_OBJECTS:LangulusEntity>
)

target_include_directories(Langulus PUBLIC
    $<TARGET_PROPERTY:LangulusLogger,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:LangulusRTTI,INTERFACE_INCLUDE_DIRECTORIES>
    $<$<BOOL:${LANGULUS_FEATURE_MANAGED_MEMORY}>:$<TARGET_PROPERTY:LangulusFractalloc,INTERFACE_INCLUDE_DIRECTORIES>>
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

if(LANGULUS_TESTING)
    add_subdirectory(testmodule)
    add_subdirectory(test)
endif()

