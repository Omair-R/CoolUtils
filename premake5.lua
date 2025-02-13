function add_files()
    files { "%{prj.location}/src/**.hpp",
            "%{prj.location}/src/**.h",
            "%{prj.location}/src/**.cpp"}
end

function filter_cfg()
    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"
end

workspace "CoolUtils"
    architecture "x64"
    configurations {"Debug", "Release"}

project "CoolUtils"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    location "CoolUtils"
    targetdir("build/bin/%{cfg.buildcfg}")
    objdir("build/obj/%{cfg.buildcfg}") 

    files { "%{prj.location}/src/**.hpp",
            "%{prj.location}/src/**.h",
            "%{prj.location}/src/**.cpp",
            }

    includedirs {
            "%{prj.location}/imports/include",
    }

    libdirs {

            "%{prj.location}/imports/lib",
    }

        
    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"
        links { 
            "fmtd.lib",
        }

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"
        links { 
            "fmt.lib",
        }

project "Testing"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    location "Testing"
    targetdir("build/testing/bin/%{cfg.buildcfg}")
    objdir("build/testing/obj/%{cfg.buildcfg}") 

    includedirs {
            "%{prj.location}/../CoolUtils/imports/include",
            "%{prj.location}/../CoolUtils/src"
    }

    links {
    "CoolUtils",
    }

    add_files()
    filter_cfg()


