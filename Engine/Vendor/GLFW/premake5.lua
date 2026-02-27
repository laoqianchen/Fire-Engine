project "GLFW"
	kind "StaticLib"
	language "C"

	targetdir ("Binaries/" ..outputdir.. "/%{prj.name}")
	objdir ("Intermediate/" ..outputdir.. "/%{prj.name}")

-- Include all GLFW source files to avoid missing symbols due to version changes or platform-specific splits
	files{
		"include/GLFW/**.h",
		"src/**.h",
		"src/**.c"
	}

	filter "system:windows"
		buildoptions { "-std=c11", "-Igdi32" }
		systemversion "latest"
		staticruntime "On"

		defines {
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter {"system:windows", "configurations:Release"}
		buildoptions "/MT"