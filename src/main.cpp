#include "network/network.h"
#include "utils/utils.h"
#include "logger/logger.h"
#include "versions/versions.h"

#include <iostream>

int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; i++)
    {
        if (strncmp(argv[i], "--debug", 32))
        {
            // do smth
        }
    }

    gen_log_file();

    if (!std::filesystem::is_directory(".minecraft/"))
    {
        utils::gen_struct();
    }
    
    network::download("launchermeta.mojang.com", "/mc/game/version_manifest.json", "version_manifest.json", ".minecraft/versions/");

    version t1_20_1{"1.20.1", "piston-meta.mojang.com/v1/packages/7b9a67b8db5959c6d401bc10abe99815de2f8856/1.20.1.json"};


    versions::get(t1_20_1);

    std::cin.get();
    return 0;
}