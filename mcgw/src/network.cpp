#include "network.h"

void network::download(const char* baseurl, const char* path2file, const char* filename, httplib::DownloadProgress progress)
{
    log_trace("network.cpp::download() | '%s' file started downloading.", filename);
    httplib::Client bmclapi(baseurl);

    bmclapi.set_keep_alive(true);
    bmclapi.set_default_headers({
        {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3"}
    });

    httplib::Result res = bmclapi.Get(path2file);

    if (res && res->status == 200)
    {
        std::ofstream ofs(filename, std::ios::binary);

        if (!ofs)  { log_error("network.cpp::download() | Failed to open file '%s' for writing.", filename); return; }

        ofs << res->body;
        ofs.close();

        log_info("network.cpp::download() | File '%s' successfully downloaded!", filename);
        return;
    }
    else
    {  
        log_warn("network.cpp::download() | Download failed. HTTP status: %d", res->status);
        return;
    }
}
