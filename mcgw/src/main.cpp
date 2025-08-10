#include "network.h"
#include "log.h"

#include <iostream>


int main(int argc, char* argv[])
{
    gen_log_file();

    
    network::download("launchermeta.mojang.com", "/mc/game/version_manifest.json", "version_manifest.json", nullptr);


    std::cin.get();
    return 0;
}