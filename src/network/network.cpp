#include "network.h"


void network::download(std::string baseurl, std::string path2file_web, 
                       std::string filename, std::string path2save, httplib::DownloadProgress progress)
{
    log_trace("network.cpp::download() -> '%s' file started downloading.", filename.c_str());
    httplib::Client bmclapi(baseurl);

    bmclapi.set_keep_alive(true);
    bmclapi.set_default_headers({
        {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3"}
    });

    httplib::Result res = bmclapi.Get(path2file_web);

    if (res && res->status == 200)
    {
        std::ofstream ofs(path2save + filename, std::ios::binary);

        if (!ofs)  { log_error("network.cpp::download() -> Failed to open file '%s' for writing. Error: %s", filename.c_str(), strerror(errno)); return; }

        ofs << res->body;
        ofs.close();

        log_info("network.cpp::download() -> File '%s' successfully downloaded!", filename.c_str());
        return;
    }
    else
    {  
        log_warn("network.cpp::download() -> Download failed. HTTP response status: %d", res->status);
        return;
    }
}


void network::download_ssl(std::string baseurl, std::string path2file_web,
    std::string filename, std::string path2save, httplib::DownloadProgress progress)
{
    log_trace("network.cpp::download_ssl() -> '%s' file started downloading.", filename.c_str());
    httplib::SSLClient bmclapi(baseurl);

    bmclapi.set_keep_alive(true);
    bmclapi.set_default_headers({
        {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3"}
        });

    httplib::Result res = bmclapi.Get(path2file_web);

    if (res && res->status == 200)
    {
        std::ofstream ofs(path2save + filename, std::ios::binary);

        if (!ofs) { log_error("network.cpp::download_ssl() -> Failed to open file '%s' for writing. Error: %s", filename.c_str(), strerror(errno)); return; }

        ofs << res->body;
        ofs.close();

        log_info("network.cpp::download_ssl() -> File '%s' successfully downloaded!", filename.c_str());
        return;
    }
    else
    {
        log_warn("network.cpp::download_ssl() -> Download failed. HTTP response status: %d", res->status);
        return;
    }
}
