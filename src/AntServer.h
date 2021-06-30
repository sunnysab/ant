//
// Created by sunnysab on 2021/6/23.
//

#pragma once

#include <fstream>
#include <string>
#include "UdpSocket.h"


using port_t = unsigned short;


class AntServer {
protected:
    // Udp socket handle
    UdpSocket socket_;
    // Output handle
    std::ofstream output_file_;
    // Directory of saving received file.
    std::string save_directory_;
    // Auto accept
    bool auto_accept_ = false;

public:
    AntServer() = default;

    AntServer(const std::string &local_addr, const port_t port);

    void set_save_directory(const std::string &path);

};
