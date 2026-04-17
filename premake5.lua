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

    files { 
        "%{prj.location}/src/**.cpp",
    }

    includedirs {
        "%{prj.location}/include",
        "/usr/include/SDL3",
    }
    
    links {
        "SDL3",
        "SDL3_image",
        "SDL3_mixer",
        "SDL3_ttf",
    }

    sanitize { "Address", "Fuzzer", "UndefinedBehavior"}

    optimize "On"
   
    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        linktimeoptimization "On"
        defines { "NDEBUG" }
