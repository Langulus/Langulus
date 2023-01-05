function(langulus_init_git_submodule NAME)
	if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${NAME}/.git" )
        # Submodule hasn't been initialized yet, so call git submodule update --init on it
        message(STATUS "Initializing submodule: ${CMAKE_CURRENT_SOURCE_DIR}/${NAME}...")
        find_package(Git REQUIRED)
        execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule update --init -- ${NAME} 
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMAND_ERROR_IS_FATAL ANY
        )
	endif()
endfunction()