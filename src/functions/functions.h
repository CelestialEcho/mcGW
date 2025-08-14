#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <iostream>
#include <cstdio>
#include <filesystem>

#include "../network/network.h"
#include "../logger/logger.h"

namespace utils
{
    void gen_struct();
    void check_jre();
    void unzip(const std::string& archive_path, const std::string& extract_path);
}

#endif /* UTILS_H */