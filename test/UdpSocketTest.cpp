//
// Created by sunnysab on 2021/6/28.
//

#include <stdexcept>
#include <winsock2.h>
#include <iostream>
#include "UdpSocket.h"
#include "gtest/gtest.h"


#define UNIT_TEST_TX_PORT   50000
#define UNIT_TEST_RX_PORT   50001


TEST(TestCase, TestListener) {
    WSADATA wsa_data;
    auto ret = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (ret != 0) {
        auto last_error_code = WSAGetLastError();
        std::cerr << "Winsock error code: " << last_error_code << std::endl;

        throw std::exception("Test case failed.");
    }

    try {
        UdpSocket tx, rx;
        byte message_buf[] = {"Hello world!"};
        std::vector<byte> message(message_buf, message_buf + sizeof(message_buf));

        tx.bind("127.0.0.1", UNIT_TEST_TX_PORT);
        rx.bind("127.0.0.1", UNIT_TEST_RX_PORT);

        tx.connect("127.0.0.1", UNIT_TEST_RX_PORT);
        tx.send(message);
        auto recv_packet = rx.recvfrom();

        tx.close();
        rx.close();

        ASSERT_TRUE(recv_packet.host == "127.0.0.1");
        ASSERT_TRUE(recv_packet.port == UNIT_TEST_TX_PORT);
        ASSERT_TRUE(recv_packet.payload == message);
    }
    catch (std::exception &e) {
        auto last_error_code = WSAGetLastError();
        std::cerr << "Catched exception: " << e.what() << std::endl;
        std::cerr << "Winsock error code: " << last_error_code << std::endl;

        throw std::exception("Test case failed.");
    }
}
