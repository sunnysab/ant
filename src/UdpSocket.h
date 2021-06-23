//
// Created by sunnysab on 2021/6/23.
//

#ifndef ANT_UDPSOCKET_H
#define ANT_UDPSOCKET_H


class UdpSocket
{

public:
    explicit UdpSocket(std::string  local_address, unsigned short  port);

    int  send(const char *buffer, unsigned int  size);
};


#endif //ANT_UDPSOCKET_H
