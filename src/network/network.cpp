#include "network.h"


void _http(std::string baseurl, std::string path2file_web, std::string filename, std::string path2save, httplib::DownloadProgress progress)
{
    log_trace("network.cpp::download() -> '%s' file started downloading.", filename.c_str());
    httplib::Client bmclapi(baseurl);

    bmclapi.set_keep_alive(true);
    bmclapi.set_default_headers({
        {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3"}
    });

    httplib::Result res = bmclapi.Get(path2file_web, progress);

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
void _https(std::string baseurl, std::string path2file_web, std::string filename, std::string path2save, httplib::DownloadProgress progress)
{
    log_trace("network.cpp::download() -> '%s' file started downloading.", filename.c_str());
    httplib::SSLClient bmclapi(baseurl);

    bmclapi.set_keep_alive(true);
    bmclapi.set_default_headers({
        {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3"}
        });

    httplib::Result res = bmclapi.Get(path2file_web, progress);

    if (res && res->status == 200)
    {
        std::ofstream ofs(path2save + filename, std::ios::binary);

        if (!ofs) { log_error("network.cpp::download() -> Failed to open file '%s' for writing. Error: %s", filename.c_str(), strerror(errno)); return; }

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


void network::download(std::string baseurl, std::string path2file_web, std::string filename, std::string path2save, const con_type& connection, httplib::DownloadProgress progress)
{
    if (connection == HTTP) { _http(baseurl, path2file_web, filename, path2save, progress); }
    if (connection == HTTPS) { _https(baseurl, path2file_web, filename, path2save, progress); }
}