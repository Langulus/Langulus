langulus_init_git_submodule(Core)

if(LANGULUS_OPTION_TESTING)
   langulus_init_git_submodule(Testing)
endif()

langulus_init_git_submodule(Logger)

if(LANGULUS_OPTION_PROFILING)
   langulus_init_git_submodule(Profiler)
endif()

langulus_init_git_submodule(RTTI)

if(LANGULUS_OPTION_MANAGED_MEMORY)
   langulus_init_git_submodule(Fractalloc)
endif()

langulus_init_git_submodule(SIMD)
langulus_init_git_submodule(Anyness)
langulus_init_git_submodule(Flow)
langulus_init_git_submodule(Entity)
langulus_init_git_submodule(Math)

# Combine all submodules as one library                                         
add_langulus_library(Langulus
   SOURCES  $<$<BOOL:${LANGULUS_OPTION_LOGGING}>:$<TARGET_OBJECTS:LangulusLogger>>
            $<TARGET_OBJECTS:LangulusRTTI>
            $<$<BOOL:${LANGULUS_OPTION_MANAGED_MEMORY}>:$<TARGET_OBJECTS:LangulusFractalloc>>
            $<$<BOOL:${LANGULUS_OPTION_PROFILING}>:$<TARGET_OBJECTS:LangulusProfiler>>
            $<TARGET_OBJECTS:LangulusAnyness>
            $<TARGET_OBJECTS:LangulusFlow>
            $<TARGET_OBJECTS:LangulusMath>
            $<TARGET_OBJECTS:LangulusEntity>
            Langulus.cpp
)

target_include_directories(Langulus
   PUBLIC 	$<$<BOOL:${LANGULUS_OPTION_LOGGING}>:$<TARGET_PROPERTY:LangulusLogger,INTERFACE_INCLUDE_DIRECTORIES>>
            $<TARGET_PROPERTY:LangulusRTTI,INTERFACE_INCLUDE_DIRECTORIES>
            $<$<BOOL:${LANGULUS_OPTION_MANAGED_MEMORY}>:$<TARGET_PROPERTY:LangulusFractalloc,INTERFACE_INCLUDE_DIRECTORIES>>
            $<$<BOOL:${LANGULUS_OPTION_PROFILING}>:$<TARGET_PROPERTY:LangulusProfiler,INTERFACE_INCLUDE_DIRECTORIES>>
            $<TARGET_PROPERTY:LangulusAnyness,INTERFACE_INCLUDE_DIRECTORIES>
            $<TARGET_PROPERTY:LangulusFlow,INTERFACE_INCLUDE_DIRECTORIES>
            $<TARGET_PROPERTY:LangulusMath,INTERFACE_INCLUDE_DIRECTORIES>
            $<TARGET_PROPERTY:LangulusEntity,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(Langulus
   PUBLIC   LangulusCore
            $<$<BOOL:${LANGULUS_OPTION_LOGGING}>:fmt>
   #PRIVATE $<$<NOT:$<BOOL:${MSVC}>>:dl>
)

target_compile_definitions(Langulus
   PRIVATE  LANGULUS_EXPORT_ALL
)

if(LANGULUS_OPTION_TESTING)
   add_subdirectory(testmodule)
   add_subdirectory(test)
endif()

