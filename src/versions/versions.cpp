#include "versions.h"



static std::string _getDir(const std::string& url) 
{
	return url.substr(url.find('/', url.find("://") + 3));
}

static std::string _getFile(const std::string& path) 
{
	size_t pos = path.find_last_of("/");
	if (pos == std::string::npos) { return path; }
	return path.substr(pos + 1);
}


void versions::get(const version& ver)
{
	std::filesystem::create_directories(".minecraft/versions/" + ver.id);
	network::download("piston-meta.mojang.com", _getDir(ver.url), ver.id + ".json", ".minecraft/versions/" + ver.id + "/");
	std::fstream version_json(".minecraft/versions/" + ver.id + "/" + ver.id + ".json", std::ios::in);
	json vj = json::parse(version_json);

	std::string client_jar = vj["downloads"]["client"]["url"];
	std::vector<std::string> libs;

	for (const auto& lib : vj["libraries"]) { libs.push_back(lib["downloads"]["artifact"]["path"]); }

	for (const auto& lib : libs) 
	{
		if (std::filesystem::exists(".minecraft/libraries/" + lib)) continue;
		std::filesystem::create_directories(std::filesystem::path(".minecraft/libraries/" + lib).parent_path());
		network::download("libraries.minecraft.net", "/" + lib, _getFile(lib), std::filesystem::path(".minecraft/libraries/" + lib).parent_path().string(), HTTPS);
	}

	network::download("https://piston-data.mojang.com", _getDir(vj["downloads"]["client"]["url"]), ver.id + ".jar", ".minecraft/versions/" + ver.id + "/");
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

}
