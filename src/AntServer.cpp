//
// Created by sunnysab on 2021/6/23.
//

#include "AntServer.h"

AntServer::AntServer(const std::string &local_addr, const port_t port)
        : socket_(local_addr, port) {

    void();
}

void AntServer::set_save_directory(const std::string &path) {

}
