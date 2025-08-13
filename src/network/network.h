#ifndef NETWORK_H
#define NETWORK_H

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <httplib.h>

#include <fstream>
#include "../logger/logger.h"

enum con_type
{
    HTTP, HTTPS
};

namespace network
{
    void download(std::string baseurl, std::string path2file_web, std::string filename, std::string path2save, 
        const con_type& connection = HTTP, httplib::DownloadProgress progress = nullptr);

    
}


#endif /* NETWORK_H */