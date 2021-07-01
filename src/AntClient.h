//
// Created by sunnysab on 2021/6/23.
//

#pragma once

#include <functional>
#include <string>
#include <string_view>
#include "protocol/RequestPayload.h"
#include "UdpSocket.h"
#include "ReadBuffer.h"


struct TransferProcess {
    size_t total_size;
    size_t completed_size;
};

class AntClient {
protected:
    // Udp Socket object
    UdpSocket socket_;

    /* File operation related */
    std::ifstream *in_;
    ReadBuffer buffer_;
    size_t file_size_;
    std::string file_path_;

    TransferProcess status_;

protected:
    static std::string_view parse_file_name(const std::string &s);

    RequestPayload *prepare_send_request();

public:
    AntClient(const std::string &path_);

    void connect(const std::string &host, const port_t port);

    bool try_send(void);

    void send(const std::function<bool(TransferProcess)> &callback);

    void close(void);
};
