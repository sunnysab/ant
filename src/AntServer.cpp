//
// Created by sunnysab on 2021/6/23.
//

#include <stdexcept>
#include <filesystem>
#include <protocol/RequestPayload.h>
#include <protocol/RecvResponse.h>
#include <protocol/DataPayload.h>
#include "AntServer.h"


AntServer::AntServer(const std::string &path_) {
    this->out_ = new std::ofstream;
    this->out_->open(path_, std::ios::out | std::ios::binary);

    if (!this->out_->is_open()) {
        std::string msg = (std::string) "Could not open this file: " + strerror(errno);
        throw std::exception(msg.c_str());
    }
}

void AntServer::listen(const std::string &host, const port_t port) {
    this->socket_.bind(host, port);
}

RequestPayload AntServer::wait() {
    auto request_bin = this->socket_.recvfrom();
    auto request = Frame::deserialize(request_bin.payload);

    return *dynamic_cast<RequestPayload *>(request.payload);
}

void AntServer::close() {
    this->socket_.close();
}

void AntServer::write(const std::function<bool(TransferProcess)> &callback) {
    auto &status = this->status_;

    status.completed_size = 0;
    status.total_size = this->file_size_;

    while (status.completed_size < status.total_size) {
        // Read from socket
        auto buffer = this->socket_.recvfrom();
        auto frame = Frame::deserialize(buffer.payload);
        auto content = ((DataPayload *) frame.payload)->content;

        this->buffer_.write(content);
        status.completed_size += content.size();

        if (!callback(status)) {
            throw std::exception("Process broken because us er cancelled.");
        }
    }
}

void AntServer::accept() {
    Frame data_frame;
    auto *payload = new RecvResponse();

    payload->response = true;
    data_frame.put(payload);

    auto buffer = data_frame.serialize();
    this->socket_.send(buffer);
}

void AntServer::decline() {
    Frame data_frame;
    auto *payload = new RecvResponse();

    payload->response = false;
    data_frame.put(payload);

    auto buffer = data_frame.serialize();
    this->socket_.send(buffer);
}
