//
// Created by sunnysab on 2021/6/23.
//

#pragma once

#include <iostream>
#include <fstream>
#include "UdpSocket.h"


class AntClient {
protected:
    // Udp socket handle
    UdpSocket socket_;
    // File path
    std::string file_path_;
    // Block size
    size_t block_size;

//protected:
//
//    // Try send file properties
//    void send_file_properties();
//
//    // Try send data
//    void send_file_content();

public:
    // Construct an Udp socket without local address.
    AntClient() = default;

    // Construct an Udp socket with local address by bind() function.
    AntClient(const std::string &local_addr, const port_t port);

    // Bind local address and port
    void bind(const std::string &local_address, port_t port);

    //Create file
    void open();

    //connect server
    void connect(const std::string &remote_address, port_t port);

    //transfer protected send function
    void send();

    //set file block
    void set_block_size();

    //get size of data or file
    void get_block_size();
};
