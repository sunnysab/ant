//
// Created by sunnysab on 2021/6/23.
//

#include <stdexcept>
#include "UdpSocket.h"

UdpSocket::UdpSocket(const std::string &local_address, unsigned short port) {
    this();

}

UdpSocket::UdpSocket() {
    this->s_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (this->s_ == INVALID_SOCKET) {
        throw std::exception("Error occurred while calling socket().");
    }
}

bool UdpSocket::bind(const std::string &local_address, unsigned short port) {
    sockaddr_in  addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.S_un.S_addr = inet_addr(local_address.c_str());
    if (::bind(this->s_, (sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR) {
        throw std::exception("Error occurred while calling bind().");
    }
    return true;
}

size_t UdpSocket::sendto(const vector<char> &buffer, const std::string &remote_address, unsigned short port) {
    sockaddr_in remoteAddr;
    remoteAddr.sin_family=AF_INET;
    remoteAddr.sin_port=port;
    remoteAddr.sin_addr.S_un.S_addr= inet_addr(remote_address.c_str());
    int ret = ::sendto(this->s_,&buffer[0],buffer.size(),0,(sockaddr *)&remoteAddr,sizeof(remoteAddr));
    if (ret == -1) {
        throw std::exception ("Error occurred while calling sendto().");
    }
    return ret;
}

size_t UdpSocket::send(const vector<char> &buffer) {
    int ret = ::sendto(this->s_,&buffer[0],buffer.size(),0,(sockaddr *)&(this->remote_addr_),sizeof(this->remote_addr_));
    if (ret == -1) {
        throw std::exception ("Error occurred while calling sendto().");
    }
    return ret;
}

void UdpSocket::connect(const std::string &remote_address, unsigned short port) {
    this->remote_addr_.sin_family=AF_INET;
    this->remote_addr_.sin_port=port;
    this->remote_addr_.sin_addr.S_un.S_addr=inet_addr(remote_address.c_str());
}

size_t UdpSocket::recvfrom(vector<char> &buffer) {

    int ret = ::recvfrom(this->s_,&buffer[0],buffer.size(),0,(sockaddr *)&(this->remote_addr_,&(sizeof(this->remote_addr_)))
    if (ret<=0) {
        throw std::exception("Error occurred while calling sendto().");
        return ret;
    }
    return ret;
}

size_t UdpSocket::recvfrom(vector<char> &buffer, const std::string &remote_address, unsigned short port) {
    this->remote_addr_.sin_family=AF_INET;
    this->remote_addr_.sin_port=port;
    this->remote_addr_.sin_addr.S_un.S_addr=inet_addr(remote_address.c_str());
    int ret = ::recvfrom(this->s_,&buffer[0],buffer.size(),0,(sockaddr *)&(this->remote_addr_,&(sizeof(this->remote_addr_)))
    if (ret<=0) {
        throw std::exception("Error occurred while calling sendto().");
        return ret;
    }
    return ret;
}

