//
// Created by sunnysab on 2021/6/23.
//

#include <stdexcept>
#include <filesystem>
#include <protocol/RequestPayload.h>
#include <protocol/RecvResponse.h>
#include <protocol/DataPayload.h>
#include "AntClient.h"


AntClient::AntClient(const std::string &path_) {
    this->in_ = new std::ifstream;
    this->in_->open(path_, std::ios::in | std::ios::binary);

    if (!this->in_->is_open()) {
        std::string msg = (std::string) "Could not open this file: " + strerror(errno);
        throw std::exception(msg.c_str());
    }
}

void AntClient::connect(const std::string &host, const port_t port) {
    this->socket_.connect(host, port);
}

bool AntClient::try_send() {
    Frame request_frame(0, 0, FrameType::SendRequest);
    RequestPayload *payload = this->prepare_send_request();
    request_frame.put(payload);
    auto buffer = request_frame.serialize();
    delete payload;
    payload = nullptr;

    this->socket_.send(buffer);
    auto received_packet = this->socket_.recvfrom();

    Frame response = Frame::deserialize(received_packet.payload);
    auto *srv_resp = dynamic_cast<RecvResponse *>(response.payload);
    auto srv_ack = srv_resp->response;
    delete srv_resp;
    srv_resp = nullptr;

    return srv_ack;
}

void AntClient::close() {
    this->socket_.close();
}

std::string_view AntClient::parse_file_name(const std::string &s) {
    auto pos_slash = s.rfind('/');
    auto pos_backslash = s.rfind('\\');
    if (pos_slash == static_cast<size_t>(-1))
        pos_slash = 0;
    else
        pos_slash++;

    if (pos_backslash == static_cast<size_t>(-1))
        pos_backslash = 0;
    else
        pos_slash++;

    auto file_name_start = pos_slash > pos_backslash ? pos_slash : pos_backslash;
    std::string_view file_name(s);

    file_name = file_name.substr(file_name_start);
    return file_name;
}

RequestPayload *AntClient::prepare_send_request() {
    std::error_code err_code;
    this->file_size_ = std::filesystem::file_size(this->file_path_, err_code);
    if (err_code.value() != 0)
        throw std::exception(err_code.message().c_str());
    auto file_name = parse_file_name(this->file_path_);

    auto *payload = new RequestPayload();
    payload->client_name = "client";
    payload->file_name = file_name;
    payload->file_size = this->file_size_;
    return payload;
}

void AntClient::send(const std::function<bool(TransferProcess)> &callback) {
    auto &status = this->status_;

    status.completed_size = 0;
    status.total_size = this->file_size_;

    while (status.completed_size < status.total_size) {
        // Read from buffer.
        auto disk_buffer = this->buffer_.read(1024);
        auto *payload = new DataPayload();
        payload->content = disk_buffer;

        Frame frame;
        frame.put(payload);
        auto net_buffer = frame.serialize();

        this->socket_.send(net_buffer);
        status.completed_size += net_buffer.size();

        if (!callback(status)) {
            throw std::exception("Process broken because user cancelled.");
        }
    }
}
