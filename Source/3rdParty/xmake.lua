-- include sub directories
includes("glad")

-- include game-activity for android
if is_plat("android") then
    includes("game-activity")
end