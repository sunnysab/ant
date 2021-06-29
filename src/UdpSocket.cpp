//
// Created by sunnysab on 2021/6/23.
//

#include <string>
#include <vector>
#include <stdexcept>
#include "UdpSocket.h"


UdpSocket::UdpSocket(const std::string &local_addr, port_t port)
        : UdpSocket() {
    // Bind with the address in parameter.
    this->bind(local_addr, port);
}

UdpSocket::UdpSocket() {
    this->s_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (INVALID_SOCKET == this->s_) {
        throw std::exception("Error occurred while calling socket().");
    }
}

void UdpSocket::bind(const std::string &local_addr, port_t port) {
    sockaddr_in &_st_local_addr = this->local_addr_;

    _st_local_addr.sin_family = AF_INET;
    _st_local_addr.sin_port = htons(port);
    _st_local_addr.sin_addr.S_un.S_addr = inet_addr(local_addr.c_str());
    if (::bind(this->s_, (sockaddr *) &_st_local_addr, sizeof(sockaddr_in)) == SOCKET_ERROR) {
        throw std::exception("Error occurred while calling bind().");
    }
}

size_t UdpSocket::sendto(const std::vector<byte> &buffer, const std::string &remote_addr, const port_t remote_port) {
    sockaddr_in st_dest_addr;

    st_dest_addr.sin_family = AF_INET;
    st_dest_addr.sin_port = htons(remote_port);
    st_dest_addr.sin_addr.S_un.S_addr = inet_addr(remote_addr.c_str());

    int sent_size = ::sendto(this->s_, reinterpret_cast<const char *>(&buffer[0]), buffer.size(), 0
                             , (sockaddr *) &st_dest_addr, sizeof(st_dest_addr));
    if (sent_size == -1) {
        throw std::exception("Error occurred while calling sendto().");
    }
    return sent_size;
}

size_t UdpSocket::send(const std::vector<byte> &buffer) {
    int sent_size = ::sendto(this->s_, reinterpret_cast<const char *>(&buffer[0]), buffer.size(), 0
                             , (sockaddr *) &(this->remote_addr_), sizeof(sockaddr_in));
    if (sent_size == -1) {
        throw std::exception("Error occurred while calling sendto().");
    }
    return sent_size;
}

void UdpSocket::connect(const std::string &local_addr, port_t remote_port) {
    sockaddr_in &_st_remote_addr = this->remote_addr_;

    _st_remote_addr.sin_family = AF_INET;
    _st_remote_addr.sin_port = htons(remote_port);
    _st_remote_addr.sin_addr.S_un.S_addr = inet_addr(local_addr.c_str());
}

size_t UdpSocket::recvfrom(std::vector<byte> &buffer, std::string &src_address, port_t &src_port) {
    sockaddr_in _st_source_addr{};
    int source_addr_len = sizeof(_st_source_addr);

    int recv_size = ::recvfrom(this->s_, reinterpret_cast<char *>(&buffer[0]), buffer.capacity(), 0
                               , (sockaddr *) &_st_source_addr, &source_addr_len);
    if (recv_size < 0) {
        throw std::exception("Error occurred while calling recvfrom().");
    }
    src_address = inet_ntoa(_st_source_addr.sin_addr);
    src_port = htons(_st_source_addr.sin_port);
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
