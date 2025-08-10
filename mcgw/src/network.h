#ifndef NETWORK_H
#define NETWORK_H

#include <httplib.h>
#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <fstream>



namespace network
{
    void download(const char* baseurl, const char* path2file, const char* filename, httplib::DownloadProgress progress);
}


#endif /* NETWORK_H */