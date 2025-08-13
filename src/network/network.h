#ifndef NETWORK_H
#define NETWORK_H

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <httplib.h>

#include <fstream>
#include "../logger/logger.h"



namespace network
{
    void download(std::string baseurl, std::string path2file_web, std::string filename, 
                  std::string path2save, httplib::DownloadProgress progress);

    void download_ssl(std::string baseurl, std::string path2file_web, std::string filename,
                      std::string path2save, httplib::DownloadProgress progress);
}


#endif /* NETWORK_H */