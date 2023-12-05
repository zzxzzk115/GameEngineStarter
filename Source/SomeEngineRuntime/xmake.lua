-- expose CLI options
option("window")
    set_showmenu(true)
    set_values("glfw", "sdl2")
    set_description("The window abstraction library, options: glfw, sdl2\ne.g.\n    - xmake f --window=glfw")
option_end()

-- choose a window abstract library (glfw, sdl2)
local window_abstract = "glfw"
local is_android = false

if has_config("window") then 
    window_abstract = get_config("window")
end

-- force override for some platforms
if is_arch("wasm.*") then -- TODO: add iOS.
    window_abstract = "sdl2"
end

-- force egl for android
if is_plat("android") then 
    window_abstract = "egl"
    is_android = true
end

-- add 3rd party dependencies
add_requires("spdlog")
add_requires("imgui v1.90-docking", {configs = {glfw = (window_abstract == "glfw"), sdl2 = (window_abstract == "sdl2"), android = is_android, opengl3 = true}})

-- define target
target("SomeEngineRuntime")

    if is_android then
        set_kind("shared")
    else
        set_kind("static")
    end

    add_files("src/**.cpp|Platform/**.cpp") -- exclude platform source

    -- add WASM support
    if is_arch("wasm.*") then
        add_defines("BUILD_EMSCRIPTEN")
    end

    -- add Android support
    if is_android then 
        add_defines("BUIILD_ANDROID")
        add_headerfiles("include/SomeEngineRuntime/Platform/Android/*.h")
        add_files("src/Platform/Android/*.cpp")
        add_deps("game-activity")
        add_links("EGL", "GLESv3", "jnigraphics", "android", "log")
    end

    -- fix missing -ldl
    if is_plat("linux") then
        add_syslinks("dl")
    end

    -- different window abstraction, add different macro defination and files
    if window_abstract == "sdl2" then
        add_defines("USE_WINDOW_ABSTRACT_SDL")
        add_files("src/Platform/WindowAbstract/SDL/**.cpp")
    elseif window_abstract == "glfw" then
        add_defines("USE_WINDOW_ABSTRACT_GLFW")
        add_files("src/Platform/WindowAbstract/GLFW/**.cpp")
    elseif window_abstract == "egl" then
        add_defines("USE_WINDOW_ABSTRACT_EGL")
        add_files("src/Platform/WindowAbstract/EGL/**.cpp")
    end

    add_deps("my_glad")
    add_packages("spdlog", {public = true})
    add_packages("imgui", {public = true})
    add_includedirs("include", {public = true}) -- public: let other targets to auto include
