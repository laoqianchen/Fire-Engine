
project "Glad"  -- quan da xie you shi hou bu he shi
	kind "StaticLib"
	language "C"

	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

	-- Include all GLAD source files to avoid missing symbols due to version changes or platform-specific splits
	files{
		"include/glad/**.h",
		"include/KHR/**.h",
		"src/**.c"
	}

	includedirs{
		"include"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

	filter {"system:windows", "configurations:Release"}
		buildoptions "/MT"