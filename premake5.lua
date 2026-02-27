-- premake5.lua

workspace "FireEngine"                     
    architecture "x64"                     
    -- Target architecture (64-bit). This defines the intended build platform.

    startproject "Sandbox"                 
    -- Default startup project when opening the generated solution.

    configurations { "Debug", "Release", "Dist" }   
    -- Build configurations:
    -- Debug   : Full debug information, no optimization.
    -- Release : Optimized build with some debug support retained.
    -- Dist    : Distribution build, stripped of logs and debug utilities.

-- Output directory format: <Configuration>-<System>-<Architecture>
-- Example: Debug-Windows-x64
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Engine/Vendor/GLFW/include"
IncludeDir["Glad"] = "Engine/Vendor/Glad/include"
IncludeDir["ImGui"] = "Engine/Vendor/ImGui"
IncludeDir["GLM"] = "Engine/Vendor/GLM/"
IncludeDir["StbImage"] = "Engine/Vendor/StbImage/"

group "Dependencies"
    include "Engine/Vendor/GLFW"  -- Include premake5.lua file
    include "Engine/Vendor/Glad"  -- Include premake5.lua file
    include "Engine/Vendor/ImGui"  -- Include premake5.lua file
group ""

---------------------------------------------------------------------
-- Engine Project (Core Engine Module)
---------------------------------------------------------------------
project "Engine"
    location "Engine"                       
    -- Project directory relative to this premake5.lua file.

    kind "SharedLib"                        
    -- Build as a shared library (DLL). Can be changed to StaticLib if needed.

    language "C++"

    staticruntime "off"  -- 关闭静态链接库环境，从而可以正确链接Dll

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir    ("Intermediate/" .. outputdir .. "/%{prj.name}")

    pchheader "enginepch.h"
    pchsource "Engine/Source/enginepch.cpp"

    -- Engine source files
    files {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
        "%{prj.name}/Vendor/StbImage/**.h",
        "%{prj.name}/Vendor/StbImage/**.cpp"
    }

    -- Third-party include directories
    includedirs {
        "%{prj.name}/Vendor/Spdlog/include",
        "%{prj.name}/Source",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.StbImage}"
    }

    links{
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    -- Platform-specific settings
    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"  
        buildoptions { "/utf-8" }
        -- Windows SDK version. If not specified, Premake may fall back to an older SDK (e.g. 8.1).

        defines {
            "ENGINE_PLATFORM_WINDOWS",
            "ENGINE_BUILD_DLL",
            "GLFW_INCLUDE_NONE",  -- 当使用GLFW时，他将不会包含任何OpenGL头文件，否则会重复包含导致编译不通过
        }

        -- %{cfg.buildtarget.relpath} represents the relative path
        -- to the final build output (e.g., Engine.dll) for the current configuration.
        -- This command copies the Engine DLL into the Sandbox output directory.
        -- 放在这里第一次构建时，Engine构建完成SandBox还不存在，会编译报错。
        -- 但是如果把这个东西放到SandBox去执行，那么如果SandBox没发生变化，但是引擎变了，就同步不过去
        -- 所以最后还是决定把这条指令放在Engine构建后执行
        postbuildcommands {
            -- "{COPY} %{cfg.buildtarget.relpath} ../Binaries/" .. outputdir .. "/Sandbox"
            "{COPY} %{cfg.buildtarget.relpath} \"../Binaries/" .. outputdir .. "/Sandbox/\""
        }

    filter "configurations:Debug"
        defines "ENGINE_DEBUG"
        -- 设置运行库为多线程DLLdebug
        -- 因为引擎项目的目标文件是dll，因此Sanbox与Engine项目使用的是两个堆
        -- 必须用这个设置，才能让程序正确的链接生成物，否则他会以为这个项目的生成物是静态的，以为是在当前程序的堆上分配的内存
        -- 如果是多线程debug（静态链接）的话，用staticruntion即可
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "ENGINE_RELEASE"
        -- 设置运行库为多线程DLL
        -- 因为引擎项目的目标文件是dll，因此Sanbox与Engine项目使用的是两个堆
        -- 必须用这个设置，才能让程序正确的链接生成物，否则他会以为这个项目的生成物是静态的，以为是在当前程序的堆上分配的内存
        -- 如果是多线程debug（静态链接）的话，用staticruntion即可
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "ENGINE_DIST"
        -- 设置运行库为多线程DLL
        -- 因为引擎项目的目标文件是dll，因此Sanbox与Engine项目使用的是两个堆
        -- 必须用这个设置，才能让程序正确的链接生成物，否则他会以为这个项目的生成物是静态的，以为是在当前程序的堆上分配的内存
        -- 如果是多线程debug（静态链接）的话，用staticruntion即可
        runtime "Release"
        optimize "on"

---------------------------------------------------------------------
-- Sandbox Project (Example Application / Entry Point)
---------------------------------------------------------------------
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"  -- 关闭静态链接库环境，从而可以正确链接Dll

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir    ("Intermediate/" .. outputdir .. "/%{prj.name}")

    -- Sandbox source files
    files {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    -- Include Engine headers
    includedirs {
        "Engine/Source",
        "Engine/Vendor/Spdlog/include",
        "Engine/Vendor/ImGui",
        "Engine/Vendor/GLM"
    }

    -- Link against the Engine shared library
    links {
        "Engine"
    }

    -- Platform-specific settings
    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"  
        buildoptions { "/utf-8" }

        defines {
            "ENGINE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "ENGINE_DEBUG"
        -- 设置运行库为多线程DLLdebug
        -- 因为引擎项目的目标文件是dll，因此Sanbox与Engine项目使用的是两个堆
        -- 必须用这个设置，才能让程序正确的链接生成物，否则他会以为这个项目的生成物是静态的，以为是在当前程序的堆上分配的内存
        -- 如果是多线程debug（静态链接）的话，用staticruntion即可
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "ENGINE_RELEASE"
        -- 设置运行库为多线程DLL
        -- 因为引擎项目的目标文件是dll，因此Sanbox与Engine项目使用的是两个堆
        -- 必须用这个设置，才能让程序正确的链接生成物，否则他会以为这个项目的生成物是静态的，以为是在当前程序的堆上分配的内存
        -- 如果是多线程debug（静态链接）的话，用staticruntion即可
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "ENGINE_DIST"
        -- 设置运行库为多线程DLL
        -- 因为引擎项目的目标文件是dll，因此Sanbox与Engine项目使用的是两个堆
        -- 必须用这个设置，才能让程序正确的链接生成物，否则他会以为这个项目的生成物是静态的，以为是在当前程序的堆上分配的内存
        -- 如果是多线程debug（静态链接）的话，用staticruntion即可
        runtime "Release"
        optimize "on"
