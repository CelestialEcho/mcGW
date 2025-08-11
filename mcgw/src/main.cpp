#include "network.h"
#include "utils.h"
#include "log.h"

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

    network::download("launchermeta.mojang.com", "/mc/game/version_manifest.json", "version_manifest.json", nullptr);
    if (std::filesystem::is_directory(".minecraft/"))
    {
        utils::gen_struct();
    }

    std::cin.get();
    return 0;
}