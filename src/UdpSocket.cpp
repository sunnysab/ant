//
// Created by sunnysab on 2021/6/23.
//

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

bool UdpSocket::bind(const std::string &local_address, port_t port) {
    this->local_addr_ = sockaddr_in{
            .sin_family = AF_INET,
            .sin_port = htons(port),
            .sin_addr.S_un.S_addr = inet_addr(local_address.c_str()),
    };
    if (::bind(this->s_, (sockaddr *) &this->local_addr_, sizeof(sockaddr_in)) == SOCKET_ERROR) {
        throw std::exception("Error occurred while calling bind().");
    }
    return true;
}

size_t UdpSocket::sendto(const vector <byte> &buffer, const std::string &remote_address, port_t remote_port) {
    sockaddr_in dest_addr{
            .sin_family = AF_INET,
            .sin_port = remote_port,
            .sin_addr.S_un.S_addr = inet_addr(remote_address.c_str()),
    };
    int sent_size = ::sendto(this->s_, &buffer[0], buffer.size(), 0, (sockaddr *) &dest_addr, sizeof(dest_addr));
    if (sent_size == -1) {
        throw std::exception("Error occurred while calling sendto().");
    }
    return sent_size;
}

size_t UdpSocket::send(const vector <byte> &buffer) {
    int sent_size = ::sendto(this->s_, &buffer[0], buffer.size(), 0, (sockaddr *) &(this->remote_addr_)
                             , sizeof(sockaddr_in));
    if (sent_size == -1) {
        throw std::exception("Error occurred while calling sendto().");
    }
    return sent_size;
}

void UdpSocket::connect(const std::string &remote_address, port_t remote_port) {
    this->remote_addr_ = sockaddr_in{
            .sin_family = AF_INET,
            .sin_port = htons(remote_port),
            .sin_addr.S_un.S_addr = inet_addr(remote_address.c_str()),
    };
}

size_t UdpSocket::recvfrom(vector <byte> &buffer, const std::string &remote_address, port_t &port) {
    sockaddr_in  source_addr {};

    int recv_size = ::recvfrom(this->s_, &buffer[0], buffer.size(), 0
                         , (sockaddr *) &source_addr, sizeof(sockaddr_in));
    if (recv_size <= 0) {
        throw std::exception("Error occurred while calling recvfrom().");
    }
    return recv_size;
}
