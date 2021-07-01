//
// Created by sunnysab on 2021/6/28.
//

#include <iostream>
#include <winsock2.h>
#include "progress_bar.h"
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
    if (opt != 'Y' && opt != 'y') {
        std::cout << "User cancelled.";
        server.decline();
        return 0;
    }

    bmc::progress_bar pb{
            0,  // min, also initial value
            request.file_size,  // max
            80,  // width in percent of screen (including percentage and time)
            true,  // auto increment when outputting
            true   // show time at the end
    };
    server.accept();
    server.write([&pb](TransferProcess process) -> bool {
        pb.set(process.completed_size);
        std::cout << pb;
        return true;
    });
    std::cout << pb;
    std::cout << "Transfer finished." << std::endl;

    WSACleanup();
    return 0;
}