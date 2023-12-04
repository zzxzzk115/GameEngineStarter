-- set project name
set_project("SomeEngine")

-- set project version
set_version("0.1.0")

set_languages("cxx17")
add_cxxflags("/Zc:__cplusplus", {tools = {"msvc", "cl"}}) -- fix __cplusplus == 199711L error

-- global rules
add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

-- add my own xmake-repo, I added support for Raspberry Pi and Emscripten.
-- you can use your own xmake-repo too.
add_repositories("my-repo https://github.com/zzxzzk115/xmake-repo.git dev")

-- include sub directories
includes("3rdParty")
includes("SomeEngineRuntime")
includes("Test/Playground/xmake.lua")