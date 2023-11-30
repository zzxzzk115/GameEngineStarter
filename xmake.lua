-- set project name
set_project("SomeEngine")

-- set project version
set_version("0.1.0")

set_languages("cxx17")
add_cxxflags("/Zc:__cplusplus", {tools = {"msvc", "cl"}}) -- fix bx/platform.h __cplusplus == 199711L error

-- global rules
add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

-- add my own xmake-repo
add_repositories("my-repo git@github.com:zzxzzk115/xmake-repo.git dev")

-- include sub directories
includes("Source/3rdParty")
includes("Source/SomeEngineRuntime")
includes("Source/Test/**/xmake.lua")