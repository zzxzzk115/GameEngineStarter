-- define target
target("my_glad")
    set_kind("static")
    add_files("src/glad.c")
    add_includedirs("include", {public = true}) -- public: let other targets to auto include