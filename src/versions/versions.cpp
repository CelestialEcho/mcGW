#include "versions.h"

// https://piston-meta.mojang.com/v1/packages/b282396af887031d2f5cdcb7cbccd547f6d0067e/1.21.8.json 


std::string _getDir(const std::string& url)
{

	std::string path;
	size_t protocol_end = url.find("://");
	size_t domain_start = (protocol_end == std::string::npos) ? 0 : protocol_end + 3;
	size_t path_start = url.find('/', domain_start);

	if (path_start == std::string::npos)
		path = "/";
	else
		path = url.substr(path_start);
	return path;
}


void versions::get(const version& ver)
{
	std::filesystem::create_directories("./minecraft/versions/" + ver.id);
	network::download("piston-meta.mojang.com", ver.url.substr(30), ver.id + ".json", "/.minecraft/versions/" + ver.id + "/", nullptr);
	std::cout << "/.minecraft/versions/" + ver.id + "/"; // TODO
}

void versions::parse(std::vector<version>* vers)
{
	std::fstream version_manifest(".minecraft/versions/version_manifest.json", std::ios::in);

	json vl = json::parse(version_manifest);

	for (const auto& ver : vl["versions"])
	{
		if (ver["type"] == "release")
		{
			version temp;
			temp.id = ver["id"];
			temp.url = ver["url"];
			vers->push_back(temp);
		}
	}
}

std::ostream& operator<<(std::ostream& os, const version& v)
{
	os << "{ version: " << v.id << ", url: " << v.url << " }";
	return os;
}

void versions::run(version version)
{
	; // :)
}
