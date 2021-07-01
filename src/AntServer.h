//
// Created by sunnysab on 2021/6/23.
//

#pragma once

#include <functional>
#include <string>
#include <string_view>
#include "protocol/RequestPayload.h"
#include "UdpSocket.h"
#include "WriteBuffer.h"

struct TransferProcess {
    size_t total_size;
    size_t completed_size;
};


class AntServer {
protected:
    // Udp Socket object
    UdpSocket socket_;

    /* File operation related */
    std::ofstream *out_ = nullptr;
    WriteBuffer *buffer_;
    size_t file_size_;
    std::string file_path_;

    TransferProcess status_;

public:
    AntServer(const std::string &path_);

    void listen(const std::string &host, const port_t port);

    RequestPayload wait();

    void accept();

    void decline();

    void write(const std::function<bool(TransferProcess)> &callback);

    void close(void);
};
