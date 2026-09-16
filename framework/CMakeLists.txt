langulus_init_git_submodule(Core)
langulus_init_git_submodule(CT)

if(LANGULUS_OPTION_TESTING)
   langulus_init_git_submodule(Testing)
endif()

langulus_init_git_submodule(Logger)

if(LANGULUS_OPTION_PROFILING)
   langulus_init_git_submodule(Percist)
endif()

langulus_init_git_submodule(RTTI)

if(LANGULUS_OPTION_MANAGED_MEMORY)
   langulus_init_git_submodule(Fractalloc)
endif()

langulus_init_git_submodule(SIMD)
langulus_init_git_submodule(Annies)
langulus_init_git_submodule(Flow)
langulus_init_git_submodule(Things)
langulus_init_git_submodule(Math)

# Combine all submodules as one library                                         
add_langulus_library(Langulus
   SOURCES  $<$<BOOL:${LANGULUS_OPTION_LOGGING}>:$<TARGET_OBJECTS:LangulusLogger>>
            $<TARGET_OBJECTS:LangulusRTTI>
            $<$<BOOL:${LANGULUS_OPTION_MANAGED_MEMORY}>:$<TARGET_OBJECTS:LangulusFractalloc>>
            $<$<BOOL:${LANGULUS_OPTION_PROFILING}>:$<TARGET_OBJECTS:LangulusPercist>>
            $<TARGET_OBJECTS:LangulusAnnies>
            $<TARGET_OBJECTS:LangulusFlow>
            $<TARGET_OBJECTS:LangulusMath>
            $<TARGET_OBJECTS:LangulusThings>
            Langulus.cpp
)

target_include_directories(Langulus
   PUBLIC   #$<TARGET_PROPERTY:LangulusCore,INTERFACE_INCLUDE_DIRECTORIES>
            #$<TARGET_PROPERTY:LangulusCT,INTERFACE_INCLUDE_DIRECTORIES>
            $<$<BOOL:${LANGULUS_OPTION_LOGGING}>:$<TARGET_PROPERTY:LangulusLogger,INTERFACE_INCLUDE_DIRECTORIES>>
            $<TARGET_PROPERTY:LangulusRTTI,INTERFACE_INCLUDE_DIRECTORIES>
            $<$<BOOL:${LANGULUS_OPTION_MANAGED_MEMORY}>:$<TARGET_PROPERTY:LangulusFractalloc,INTERFACE_INCLUDE_DIRECTORIES>>
            $<$<BOOL:${LANGULUS_OPTION_PROFILING}>:$<TARGET_PROPERTY:LangulusPercist,INTERFACE_INCLUDE_DIRECTORIES>>
            $<TARGET_PROPERTY:LangulusAnnies,INTERFACE_INCLUDE_DIRECTORIES>
            $<TARGET_PROPERTY:LangulusFlow,INTERFACE_INCLUDE_DIRECTORIES>
            $<TARGET_PROPERTY:LangulusMath,INTERFACE_INCLUDE_DIRECTORIES>
            $<TARGET_PROPERTY:LangulusThings,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(Langulus
   PUBLIC   LangulusCore
            LangulusCT
            $<$<BOOL:${LANGULUS_OPTION_LOGGING}>:fmt>
   #PRIVATE $<$<NOT:$<BOOL:${MSVC}>>:dl>
)

target_compile_definitions(Langulus
   PRIVATE  LANGULUS_EXPORT_ALL
)
