#include "functions.h"

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
    if (!std::filesystem::is_directory(".minecraft/"))
    {
        log_warn("utils.cpp::gen_struct() -> Minecraft stucture already generated.");
        std::string directories[] = { ".minecraft/versions", ".minecraft/libraries", ".minecraft/assets",
                                 ".minecraft/resourcepacks", ".minecraft/saves", ".minecraft/screenshots",
                                 ".minecraft/logs", ".minecraft/jre_runtime", ".minecraft/bin"};

        for (const std::string& dir : directories)
        {
            std::filesystem::create_directories(dir);
            if (std::filesystem::is_directory(dir))
            {
                log_trace("utils.cpp::gen_struct() -> Directory '%s' succesfully created.", dir.c_str());
            }

        }
    }
}

// https://api.adoptium.net/v3/binary/latest/24/ga/windows/x64/jdk/hotspot/normal/adoptium


void utils::check_jre()
{
    if (!std::filesystem::is_directory(".minecraft/jre_runtime/jre_24"))
    {
        network::download("https://api.adoptium.net", "/v3/binary/latest/24/ga/windows/x64/jdk/hotspot/normal/adoptium", "jre_24_zipped.zip", ".minecraft/jre_runtime/jre_24/", HTTPS);
        utils::unzip(".minecraft/jre_runtime/jre_24/jre_24_zipped.zip", ".minecraft/jre_runtime/jre_24/");
        std::filesystem::remove("jre_24_zipped.zip");
    }
}

void utils::unzip(const std::string& archive_path, const std::string& extract_path) // TODO
{
    std::string cmd = "powershell -Command \"Expand-Archive -Path '" + archive_path + "' -DestinationPath '" + extract_path + "' -Force\"";
    std::system(cmd.c_str());
}
