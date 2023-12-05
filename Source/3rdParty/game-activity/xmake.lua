-- source from https://dl.google.com/dl/android/maven2/androidx/games/games-activity/1.2.2/games-activity-1.2.2.aar

target("game-activity")
    set_kind("static")
    add_headerfiles("**/*.h")
    add_files("**/*.cpp")
    add_includedirs("include", {public = true}) -- public: let other targets to auto include