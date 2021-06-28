//
// Created by sunnysab on 2021/6/23.
//

#include <string>
#include <vector>
#include <stdexcept>
#include "UdpSocket.h"


UdpSocket::UdpSocket(const std::string &local_address, port_t port)
        : UdpSocket() {
    // Bind with the address in parameter.
    this->bind(local_address, port);
}

UdpSocket::UdpSocket() {
    this->s_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (INVALID_SOCKET == this->s_) {
        throw std::exception("Error occurred while calling socket().");
    }
}

void UdpSocket::bind(const std::string &local_address, port_t port) {
    sockaddr_in  &local_addr = this->local_addr_;

    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(port);
    local_addr.sin_addr.S_un.S_addr = inet_addr(local_address.c_str());
    if (::bind(this->s_, (sockaddr *) &this->local_addr_, sizeof(sockaddr_in)) == SOCKET_ERROR) {
        throw std::exception("Error occurred while calling bind().");
    }
}

size_t UdpSocket::sendto(const std::vector<byte> &buffer, const std::string &remote_address, port_t remote_port) {
    sockaddr_in dest_addr;

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(remote_port);
    dest_addr.sin_addr.S_un.S_addr = inet_addr(remote_address.c_str());

    int sent_size = ::sendto(this->s_, reinterpret_cast<const char *>(&buffer[0]), buffer.size(), 0, (sockaddr *) &dest_addr, sizeof(dest_addr));
    if (sent_size == -1) {
        throw std::exception("Error occurred while calling sendto().");
    }
    return sent_size;
}

size_t UdpSocket::send(const std::vector<byte> &buffer) {
    int sent_size = ::sendto(this->s_, reinterpret_cast<const char *>(&buffer[0]), buffer.size(), 0, (sockaddr *) &(this->remote_addr_)
                             , sizeof(sockaddr_in));
    if (sent_size == -1) {
        throw std::exception("Error occurred while calling sendto().");
    }
    return sent_size;
}

void UdpSocket::connect(const std::string &remote_address, port_t remote_port) {
    sockaddr_in  &remote_addr = this->remote_addr_;

    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(remote_port);
    remote_addr.sin_addr.S_un.S_addr = inet_addr(remote_address.c_str());
}

size_t UdpSocket::recvfrom(std::vector<byte> &buffer, std::string &src_address, port_t &src_port) {
    sockaddr_in  st_source_addr {};
    int source_addr_len = sizeof(st_source_addr);

    int recv_size = ::recvfrom(this->s_, reinterpret_cast<char *>(&buffer[0]), buffer.capacity(), 0
                               , (sockaddr *) &st_source_addr, &source_addr_len);
    if (recv_size < 0) {
        throw std::exception("Error occurred while calling recvfrom().");
    }
    src_address = inet_ntoa(st_source_addr.sin_addr);
    src_port = htons(st_source_addr.sin_port);
    return recv_size;
}

UdpPacket UdpSocket::recvfrom(size_t  max_size) {
    std::string  address;
    port_t  port;
    std::vector<byte>  buffer(max_size);

    auto  recv_size = this->recvfrom(buffer, address, port);
    buffer.resize(recv_size);
    return UdpPacket {
        address, port, std::move(buffer)
    };
}

void UdpSocket::close() {
    closesocket(this->s_);
    s_ = INVALID_SOCKET;
}
