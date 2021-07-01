//
// Created by sunnysab on 2021/6/28.
//

#include <iostream>
#include <winsock2.h>
#include "AntServer.h"


int main(int argc, char *argv[]) {
    WSAData data{};
    WSAStartup(MAKEWORD(2, 2), &data);

    AntServer server("./test/test-case/received.txt");

    server.listen("0.0.0.0", 16006);
    auto request = server.wait();

    std::cout << "Received sender request: " << std::endl;
    std::cout << "File name: " << request.file_name << std::endl;
    std::cout << "File size: " << request.file_size << std::endl;
    std::cout << "File id: " << request.file_id << std::endl;

    std::cout << "Accept or not? [Y/N]: ";
    char opt = getchar();
    if (opt != 'Y') {
        std::cout << "User cancelled.";
        server.decline();
        return 0;
    }

    server.accept();
    server.write([](TransferProcess process) -> bool {
        std::cout << process.completed_size / process.total_size << std::endl;

        return true;
    });

    WSACleanup();
    return 0;
}