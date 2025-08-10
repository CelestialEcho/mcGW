#include "network.h"
#include "log.h"

#include <iostream>


int main(int argc, char* argv[])
{
    network::download("launchermeta.mojang.com", "/mc/game/version_manifest.json", "version_manifest.json", nullptr);
    
    gen_log_file();

    std::cin.get();
    return 0;
}