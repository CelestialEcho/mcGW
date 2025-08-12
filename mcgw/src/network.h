#ifndef NETWORK_H
#define NETWORK_H

#include <httplib.h>
#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <fstream>
#include "log.h"



namespace network
{
    void network::download(std::string baseurl, std::string path2file_web, std::string filename, std::string path2save, httplib::DownloadProgress progress);
}


#endif /* NETWORK_H */