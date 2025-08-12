#ifndef VERSIONS_H
#define VERSIONS_H

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

#include "../logger/logger.h"
#include "../network/network.h"

#include <json.hpp>

using json = nlohmann::json;



typedef struct version
{
    std::string id;
    std::string url;
} version;

std::ostream& operator<<(std::ostream& os, const version& v);

namespace versions
{
	void get(const version& ver);
	void parse(std::vector<version>* vers);
	void run(version version);
}

#endif /* VERSION_H */