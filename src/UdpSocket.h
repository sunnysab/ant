//
// Created by sunnysab on 2021/6/23.
//

#pragma once

#include <vector>
#include <winsock2.h>

using byte = unsigned char;
using port_t = unsigned short;


struct UdpPacket {
public:
    // Host addr, source or destination
    std::string  host;
    port_t  port;

    // Payload
    std::vector<byte>  payload;
};


class UdpSocket {
public:
    static constexpr size_t DefaultBufferSize = 1500;

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
    void bind(const std::string &local_address, port_t port);

    // Send datagram to the given address and port.
    size_t sendto(const std::vector<byte> &buffer, const std::string &remote_address, port_t remote_port);

    // Send datagram to the set address and port.
    size_t send(const std::vector<byte> &buffer);

    // Block and wait an Udp packet in,
    // and then set source address to `remote_address`, set source port to `port`.
    size_t recvfrom(std::vector <byte> &buffer, std::string &src_address, port_t &src_port);

    UdpPacket  recvfrom(const size_t  max_size = DefaultBufferSize);

    // Close socket
    void  close();
};
