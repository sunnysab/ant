//
// Created by sunnysab on 2021/6/23.
//
#include <iostream>
#include <winsock2.h>

using byte = unsigned char;
using port_t = unsigned short;


class UdpSocket {
public:
    constexpr DefaultBufferSize = 1500;

private:
    // Windows socket handle
    SOCKET s_ = INVALID_SOCKET;

    // Local address and port
    sockaddr_in local_addr_ {};
    // Set default remote address and port
    sockaddr_in remote_addr_{};

public:
    // Construct an Udp socket without local address.
    UdpSocket();

    // Construct an Udp socket with local address by bind() function.
    UdpSocket(const std::string &remote_address, port_t port);

    // Set remote host and port, to avoid filling address each call.
    void connect(const std::string &local_address, port_t port);

    // Bind local address and port. */
    bool bind(const std::string &local_address, port_t port);

    // Send datagram to the given address and port.
    size_t sendto(const vector <byte> &buffer, const std::string &remote_address, port_t remote_port);

    // Send datagram to the set address and port.
    size_t send(const vector <byte> &buffer);

    // Block and wait an Udp packet in,
    // and then set source address to `remote_address`, set source port to `port`. */
    size_t recvfrom(vector <byte> &buffer, const std::string &remote_address, port_t port);

};


#endif //ANT_UDPSOCKET_H
