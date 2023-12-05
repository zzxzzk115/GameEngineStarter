-- define target
target("Playground")
    set_kind("binary")
    add_files("*.cpp")
    add_deps("SomeEngineRuntime")