---@diagnostic disable: undefined-global
workspace "MyWorkspace"
    configurations { "Debug", "Release" }

project "GameEngine"
    kind "StaticLib"
    location "./"
    targetdir ("%{prj.location}/bin")
    objdir ("%{prj.location}/bin/build/")
    uuid ("6FE7D090-E399-11F0-B558-0800200C9A66")

    language "C++"
    cppdialect "C++17"

    files { 
        "%{prj.location}/src/**.cpp",
    }

    includedirs {
        "%{prj.location}/include",
    }

    filter { "system:macosx" }
        includedirs { "/opt/homebrew/include" }
        libdirs { "/opt/homebrew/lib" }

    filter { "system:linux" }
        includedirs { "/usr/include/SDL3" }

    filter {}
    
    links {
        "SDL3",
        "SDL3_image",
        "SDL3_mixer",
        "SDL3_ttf",
    }

    filter { "system:macosx" }
        sanitize { "Address", "UndefinedBehavior"}
    filter { "system:linux" }
        sanitize { "Address", "Fuzzer", "UndefinedBehavior"}
    filter {}

    optimize "On"
   
    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        linktimeoptimization "On"
        defines { "NDEBUG" }
