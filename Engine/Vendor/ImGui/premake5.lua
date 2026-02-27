
project "ImGui"
    kind "StaticLib"
    language "C++"

    targetdir ("Binaries/"..outputdir.."/%{prj.name}")
    objdir ("Intermediate/"..outputdir.."/%{prj.name}")

    files{
        "imconfig.h",
        "imgui.h",
        "imgui.cpp",
        "imgui_draw.cpp",
        "imgui_widgets.cpp",
        "imstb_rectpack.h",
        "imstb_textedit.h",
        "imstb_truetype.h",
        "imgui_demo.cpp",
        "imgui_tables.cpp"
    }

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "On"

        defines { "IMGUI_API=__declspec(dllexport)" }

    filter {"system:windows", "configurations:Release"}
        buildoptions "/MT"
