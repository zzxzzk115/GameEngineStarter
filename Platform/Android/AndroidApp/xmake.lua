add_rules("mode.debug", "mode.release")

includes("game-activity")

-- define target
target("someengineandroidexample")
    set_kind("shared")
    add_files("*.cpp")
    add_deps("game-activity")
    add_links("EGL", "GLESv3", "jnigraphics", "android", "log")