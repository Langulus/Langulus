#langulus_init_git_submodule(Mod-FileSystem)
#add_subdirectory(Mod-FileSystem)

if (${LANGULUS_TOASTER_MODE})
	message(STATUS "[FEATURE] Toaster mode enabled - all graphics modules disabled")
else()
	langulus_init_git_submodule(Mod-GLFW)
	add_subdirectory(Mod-GLFW)

	#langulus_init_git_submodule(Mod-ImGui)
	#add_subdirectory(Mod-ImGui)

	langulus_init_git_submodule(Mod-Vulkan)
	add_subdirectory(Mod-Vulkan)
endif()

#langulus_init_git_submodule(Mod-Assets-Images)
#add_subdirectory(Mod-Assets-Images)

#langulus_init_git_submodule(Mod-Assets-Geometry)
#add_subdirectory(Mod-Assets-Geometry)

#langulus_init_git_submodule(Mod-Assets-Materials)
#add_subdirectory(Mod-Assets-Materials)

langulus_init_git_submodule(Mod-FTXUI)
add_subdirectory(Mod-FTXUI)

#langulus_init_git_submodule(Mod-Physics)
#add_subdirectory(Mod-Physics)

#langulus_init_git_submodule(Mod-ASCII)
#add_subdirectory(Mod-ASCII)

#langulus_init_git_submodule(Mod-InputSDL)
#add_subdirectory(Mod-InputSDL)

#langulus_init_git_submodule(Mod-AI)
#add_subdirectory(Mod-AI)

#langulus_init_git_submodule(Mod-Life)
#add_subdirectory(Mod-Life)

#langulus_init_git_submodule(Mod-Network)
#add_subdirectory(Mod-Network)

#langulus_init_git_submodule(Mod-Storyteller)
#add_subdirectory(Mod-Storyteller)

#langulus_init_git_submodule(Mod-UMS)
#add_subdirectory(Mod-UMS)
