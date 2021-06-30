//
// Created by sunnysab on 2021/6/23.
//
#include <iostream>
#include <fstream>
#include "AntClient.h"
#include "UdpSocket.h"


AntClient::AntClient(const std::string &local_addr, const port_t port) {
    this->bind(local_addr, port);
}

void AntClient::bind(const std::string &local_address, port_t port) {
    this->socket_.bind(local_address, port);
}

void AntClient::open() {
    this->input_file_.open(this->file_path_, std::ios::in);
}

void AntClient::connect(const std::string &remote_address, port_t port) {
    this->socket_.connect(remote_address, port);
}

void AntClient::send() {
    this->socket_.send(this->input_file_);
}

void AntClient::set_block_size() {

}

void AntClient::get_block_size() {

}

