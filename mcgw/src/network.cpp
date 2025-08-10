#include "network.h"

/*

    httplib::Client bmclapi("https://bmclapi2.bangbang93.com");

    https://bmclapi2.bangbang93.com/mc/game/version_manifest.json

    httplib::DownloadProgress progress;
    bmclapi.Get("/mc/game/version_manifest.json", progress);

*/

// https://codesignal.com/learn/courses/efficient-api-interactions-with-cpp/lessons/downloading-files-from-an-api-in-cpp

void network::download(const char* baseurl, const char* path2file, const char* filename, httplib::DownloadProgress progress)
{
    //spdlog::info("network.cpp::download() | {} file started downloading.", filename);
    httplib::Client bmclapi(baseurl);

    bmclapi.set_keep_alive(true);
    bmclapi.set_default_headers({
        {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3"}
    });

    httplib::Result res = bmclapi.Get(path2file);


    if (res && res->status == 200)
    {
        std::ofstream ofs(filename, std::ios::binary);

        if (!ofs) { return; } // TODO: Logger

        ofs << res->body;
        ofs.close();

        return; //TODO: Logger
    }
    else {  return; //TODO: Logger      res->status 
    }
}