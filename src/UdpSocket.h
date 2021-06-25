//
// Created by sunnysab on 2021/6/23.
//
#include <iostream>
#include <winsock2.h>


class UdpSocket
{
private:
    SOCKET  s_ = INVALID_SOCKET;
    sockaddr_in  remote_addr_ {};

public:
    UdpSocket();
    UdpSocket(const std::string  &remote_address, unsigned short  port);
    void  connect(const std::string  &local_address, unsigned short port);
    bool  bind(const std::string  &local_address, unsigned short port);
    size_t  sendto(const vector<char> &buffer, const std::string &remote_address, unsigned short port);
    size_t  send(const vector<char> &buffer);
    size_t  recvfrom(vector<char> &buffer, const std::string &remote_address, unsigned short port);
    size_t  recvfrom(vector<char> &buffer)

};


#endif //ANT_UDPSOCKET_H
