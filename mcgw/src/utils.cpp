#include "utils.h"


/*

.minecraft/
├── versions/
├── libraries/
├── assets/
├── resourcepacks/
├── saves/
├── screenshots/
└── logs/

*/


void utils::gen_struct()
{
    std::string directories[] = {".minecraft/versions", ".minecraft/libraries", ".minecraft/assets",
                                 ".minecraft/resourcepacks", ".minecraft/saves", ".minecraft/screenshots",
                                 ".minecraft/logs", ".minecraft/mcgw_logs"}; 
    
    for (const std::string& dir : directories)
    {
        std::filesystem::create_directories(dir);
        if (std::filesystem::is_directory(dir))
        {
            log_trace("utils.cpp::gen_struct() -> Directory '%s' succesfully created.", dir.c_str());
        }
        
    }
}